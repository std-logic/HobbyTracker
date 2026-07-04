#include "BooksWidgetMain.h"
#include "BooksWidgetControl.h"
#include "BooksWidgetSummary.h"
#include "BooksWidgetData.h"
#include "BooksWidgetDataList.h"
#include "BooksWidgetChart.h"
#include "BooksWidgetSettings.h"
#include "../common/BooksCommon.h"
#include "../data/BooksDataConverter.h"

#include <gui/base/data/BaseExtraConverter.h>
#include <gui/base/widgets/BaseWidgetExtra.h>
#include <gui/base/widgets/BaseWidgetExtraList.h>

#include <storage/Storage.h>

#include <QMessageBox>

Books::WidgetMain::WidgetMain(QWidget* parent)
	: Base::WidgetMain{parent}
{
	initWidgets();
	initConnections();
}

void Books::WidgetMain::start()
{
	_widget_control->start();

	_settings.load();
	readCsvData(_settings.csvSettings());
}

void Books::WidgetMain::initWidgets()
{
	addWidget(_widget_control = new WidgetControl(this), 0, Qt::AlignTop);

	addWidget(_widget_summary = new WidgetSummary(this), 1, Qt::AlignTop);

	addWidget(_widget_data_list = new WidgetDataList(this), 100);

	addWidget(_widget_extra_list = new Base::WidgetExtraList(this), 100);

	addWidget(_widget_chart = new WidgetChart(this), 100);
}

void Books::WidgetMain::initConnections()
{
	connect(_widget_control, &WidgetControl::showDataList,
			_widget_data_list, &WidgetDataList::setVisible);
	connect(_widget_control, &WidgetControl::collapseDataList,
			_widget_data_list, &WidgetDataList::collapseAll);
	connect(_widget_control, &WidgetControl::expandDataList,
			_widget_data_list, &WidgetDataList::expandAll);
	connect(_widget_control, &WidgetControl::setDataListViewMode,
			_widget_data_list, &WidgetDataList::setViewMode);

	connect(_widget_control, &WidgetControl::showExtraList,
			_widget_extra_list, &Base::WidgetExtraList::setVisible);
	connect(_widget_control, &WidgetControl::collapseExtraList,
			_widget_extra_list, &Base::WidgetExtraList::collapseAll);
	connect(_widget_control, &WidgetControl::expandExtraList,
			_widget_extra_list, &Base::WidgetExtraList::expandAll);

	connect(_widget_control, &WidgetControl::showChart,
			_widget_chart, &WidgetChart::setVisible);
	connect(_widget_control, &WidgetControl::setChartViewMode,
			_widget_chart, &WidgetChart::setViewMode);

	connect(_widget_control, &WidgetControl::saveCsvData,
			this, &WidgetMain::saveCsvData);
	connect(_widget_control, &WidgetControl::addData,
			this, &WidgetMain::addData);
	connect(_widget_control, &WidgetControl::addExtra,
			this, &WidgetMain::addExtra);
	connect(_widget_control, &WidgetControl::showSettings,
			this, &WidgetMain::showSettings);

	connect(this, &WidgetMain::highlightButtonSave,
			_widget_control, &WidgetControl::highlightButtonSave);

	connect(_widget_data_list, &WidgetDataList::needUpdate,
			this, &WidgetMain::updateDataList);
	connect(_widget_data_list, &WidgetDataList::editData,
			this, &WidgetMain::editData);
	connect(_widget_data_list, &WidgetDataList::deleteData,
			this, &WidgetMain::deleteData);

	connect(_widget_extra_list, &Base::WidgetExtraList::needUpdate,
			this, &WidgetMain::updateExtraList);
	connect(_widget_extra_list, &Base::WidgetExtraList::editData,
			this, &WidgetMain::editExtra);
	connect(_widget_extra_list, &Base::WidgetExtraList::deleteData,
			this, &WidgetMain::deleteExtra);

	connect(_widget_chart, &WidgetChart::needUpdate,
			this, &WidgetMain::updateChart);
}

void Books::WidgetMain::showSettings()
{
	if (!_widget_settings) {
		_widget_settings = new WidgetSettings(_settings, this);
		connect(_widget_settings, &WidgetSettings::readCsvData,
				this, &WidgetMain::readCsvData);
		connect(_widget_settings, &WidgetSettings::saveSettings,
				this, &WidgetMain::saveSettings);
	}
	_widget_settings->open();
}

void Books::WidgetMain::saveSettings(const Settings& settings)
{
	_settings = settings;
	_settings.save();
	readCsvData(_settings.csvSettings());
}

void Books::WidgetMain::readCsvData(const Csv::Settings& csv_settings)
{
	auto csv_data = Storage::readCsv(CsvFileData, csv_settings);
	_data_list = DataConverter::conv(csv_data);
	updateAll();

	csv_data = Storage::readCsv(CsvFileExtra, csv_settings);
	_extra_list = Base::ExtraConverter::conv(csv_data);
	updateExtraList();
}

void Books::WidgetMain::saveCsvData()
{
	auto csv_data = DataConverter::conv(_data_list.value());
	auto write_data_ok = Storage::writeCsv(CsvFileData, _settings.csvSettings(), csv_data);

	csv_data = Base::ExtraConverter::conv(_extra_list.value());
	auto write_extra_ok = Storage::writeCsv(CsvFileExtra, _settings.csvSettings(), csv_data);

	if (write_data_ok && write_extra_ok) {
		emit highlightButtonSave(false);
		emit showMessage(tr("Данные сохранены"));
	} else {
		emit showMessage(tr("Ошибка записи в файл!"));
	}
}

void Books::WidgetMain::addData()
{
	showData(_data_list.value().size());
}

void Books::WidgetMain::editData(const QString& id)
{
	if (auto i = _data_list.value().findIndexById(id); i >= 0) {
		showData(i);
	}
}

void Books::WidgetMain::showData(size_t index)
{
	if (!_widget_data) {
		_widget_data = new WidgetData(index, _data_list.value(), this);
		connect(_widget_data, &WidgetData::showMessage,
				this, &WidgetMain::showMessage);
		connect(_widget_data, &WidgetData::saveData,
				this, &WidgetMain::saveData);
	}
	_widget_data->open();
}

void Books::WidgetMain::saveData(size_t index, const Data& data)
{
	if (index < _data_list.value().size()) {
		if (_data_list.value()[index] == data) { return; }
		_data_list.value()[index] = data;
	} else {
		_data_list.value().add(data);
	}

	updateAll();
	emit highlightButtonSave(true);
}

void Books::WidgetMain::deleteData(const QString& id)
{
	if (auto i = _data_list.value().findIndexById(id); i >= 0) {
		deleteDataAtIndex(i);
	}
}

void Books::WidgetMain::deleteDataAtIndex(size_t index)
{
	auto ans = QMessageBox::question(
			this,
			tr("Удаление данных"),
			tr("Удалить произведение \"%1\"?")
				.arg(_data_list.value()[index].autorAndTitleTr()));

	if (ans == QMessageBox::Yes) {
		_data_list.value().del(index);
		updateAll();
		emit highlightButtonSave(true);
	}
}

void Books::WidgetMain::addExtra()
{
	showExtra(_extra_list.value().size());
}

void Books::WidgetMain::editExtra(const QString& id)
{
	if (auto i = _extra_list.value().findIndexById(id); i >= 0) {
		showExtra(i);
	}
}

void Books::WidgetMain::showExtra(size_t index)
{
	if (!_widget_extra) {
		_widget_extra = new Base::WidgetExtra(index, _extra_list.value(), this);
		connect(_widget_extra, &Base::WidgetExtra::showMessage,
				this, &WidgetMain::showMessage);
		connect(_widget_extra, &Base::WidgetExtra::saveExtra,
				this, &WidgetMain::saveExtra);
	}
	_widget_extra->open();
}

void Books::WidgetMain::saveExtra(size_t index, const Base::Extra& extra)
{
	if (index < _extra_list.value().size()) {
		if (_extra_list.value()[index] == extra) { return; }
		_extra_list.value()[index] = extra;
	} else {
		_extra_list.value().add(extra);
	}

	updateExtraList();
	emit highlightButtonSave(true);
}

void Books::WidgetMain::deleteExtra(const QString& id)
{
	if (auto i = _extra_list.value().findIndexById(id); i >= 0) {
		deleteExtraAtIndex(i);
	}
}

void Books::WidgetMain::deleteExtraAtIndex(size_t index)
{
	auto ans = QMessageBox::question(
			this,
			tr("Удаление данных"),
			tr("Удалить запись \"%1\"?")
				.arg(_extra_list.value()[index].title()));

	if (ans == QMessageBox::Yes) {
		_extra_list.value().del(index);
		updateExtraList();
		emit highlightButtonSave(true);
	}
}

void Books::WidgetMain::updateAll()
{
	updateSummary();
	updateDataList();
	updateChart();
}

void Books::WidgetMain::updateSummary()
{
	if (_data_list.has_value()) { _widget_summary->update(_data_list.value()); }
}

void Books::WidgetMain::updateDataList()
{
	if (_data_list.has_value()) { _widget_data_list->update(_data_list.value()); }
}

void Books::WidgetMain::updateExtraList()
{
	if (_extra_list.has_value()) { _widget_extra_list->update(_extra_list.value()); }
}

void Books::WidgetMain::updateChart()
{
	if (_data_list.has_value()) { _widget_chart->update(_data_list.value()); }
}
