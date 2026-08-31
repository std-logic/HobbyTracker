#include "CoinsWidgetMain.h"
#include "CoinsWidgetControl.h"
#include "CoinsWidgetSummary.h"
#include "CoinsWidgetData.h"
#include "CoinsWidgetDataList.h"
#include "CoinsWidgetChart.h"
#include "CoinsWidgetSettings.h"
#include "../common/CoinsCommon.h"
#include "../data/CoinsDataConverter.h"

#include <gui/base/data/BaseExtraConverter.h>
#include <gui/base/widgets/BaseWidgetExtra.h>
#include <gui/base/widgets/BaseWidgetExtraList.h>

#include <storage/Storage.h>
#include <storage/csv/CsvData.h>

Coins::WidgetMain::WidgetMain(QWidget* parent)
	: Base::WidgetMain{parent}
{
	initWidgets();
	initConnections();
}

void Coins::WidgetMain::start()
{
	_widget_control->start();

	_settings.load();
	readCsvData(_settings.csvSettings());
}

void Coins::WidgetMain::initWidgets()
{
	addWidget(_widget_control = new WidgetControl(this), 0, Qt::AlignTop);
	addWidget(_widget_summary = new WidgetSummary(this), 1, Qt::AlignTop);
	addWidget(_widget_data_list = new WidgetDataList(this), 100);
	addWidget(_widget_extra_list = new Base::WidgetExtraList(this), 100);
	addWidget(_widget_chart = new WidgetChart(this), 100);
}

void Coins::WidgetMain::initConnections()
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

void Coins::WidgetMain::showSettings()
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

void Coins::WidgetMain::saveSettings(const Settings& settings)
{
	_settings = settings;
	_settings.save();
	emit showMessage(tr("Настройки сохранены"));
}

void Coins::WidgetMain::readCsvData(const Csv::Settings& csv_settings)
{
	auto csv_data = Storage::readCsv(CsvFileData, csv_settings);
	_data_list = DataConverter::conv(csv_data);

	csv_data = Storage::readCsv(CsvFileExtra, csv_settings);
	_extra_list = Base::ExtraConverter::conv(csv_data);

	updateAll();
}

void Coins::WidgetMain::saveCsvData()
{
	// we don't write main data file at this moment, because take it from external source
	// auto csv_data = DataConverter::conv(_data_list);
	// auto write_data_ok = Storage::writeCsv(CsvFileData, _settings.csvSettings(), csv_data);

	auto csv_data = Base::ExtraConverter::conv(_extra_list);
	auto write_extra_ok = Storage::writeCsv(CsvFileExtra, _settings.csvSettings(), csv_data);

	if (/*write_data_ok && */write_extra_ok) {
		_widget_control->highlightButtonSave(false);
		emit showMessage(tr("Данные сохранены"));
	} else {
		emit showMessage(tr("Ошибка записи в файл!"));
	}
}

void Coins::WidgetMain::addData()
{
	showData(_data_list.size());
}

void Coins::WidgetMain::editData(const QString& id)
{
	if (auto i = _data_list.findIndexById(id); i >= 0) {
		showData(i);
	}
}

void Coins::WidgetMain::showData(size_t index)
{
	if (!_widget_data) {
		_widget_data = new WidgetData(index, _data_list, this);
		connect(_widget_data, &WidgetData::showMessage,
				this, &WidgetMain::showMessage);
		connect(_widget_data, &WidgetData::saveData,
				this, &WidgetMain::saveData);
	}
	_widget_data->open();
}

void Coins::WidgetMain::saveData(size_t index, const Data& data)
{
	if (_data_list.set(index, data)) {
		updateDependentOnData();
		_widget_control->highlightButtonSave(true);
	}
}

void Coins::WidgetMain::deleteData(const QString& id)
{
	if (auto i = _data_list.findIndexById(id); i >= 0) {
		if (askDel(tr("Удалить \"%1\"?").arg(_data_list[i].value()))) {
			_data_list.del(i);
			updateDependentOnData();
			_widget_control->highlightButtonSave(true);
		}
	}
}

void Coins::WidgetMain::addExtra()
{
	showExtra(_extra_list.size());
}

void Coins::WidgetMain::editExtra(const QString& id)
{
	if (auto i = _extra_list.findIndexById(id); i >= 0) {
		showExtra(i);
	}
}

void Coins::WidgetMain::showExtra(size_t index)
{
	if (!_widget_extra) {
		_widget_extra = new Base::WidgetExtra(index, _extra_list, this);
		_widget_extra->addSpecialGroup(
				tr("[Синонимы для стран]"),
				tr("Перечисление через запятую стран,\nкоторые должны объединяться в одну"),
				tr("Общее название для вышеуказанных стран")
		);
		connect(_widget_extra, &Base::WidgetExtra::showMessage,
				this, &WidgetMain::showMessage);
		connect(_widget_extra, &Base::WidgetExtra::saveExtra,
				this, &WidgetMain::saveExtra);
	}
	_widget_extra->open();
}

void Coins::WidgetMain::saveExtra(size_t index, const Base::Extra& extra)
{
	if (_extra_list.set(index, extra)) {
		updateDependentOnExtra();
		_widget_control->highlightButtonSave(true);
	}
}

void Coins::WidgetMain::deleteExtra(const QString& id)
{
	if (auto i = _extra_list.findIndexById(id); i >= 0) {
		if (askDel(tr("Удалить запись \"%1\"?").arg(_extra_list[i].title()))) {
			_extra_list.del(i);
			updateDependentOnExtra();
			_widget_control->highlightButtonSave(true);
		}
	}
}

void Coins::WidgetMain::updateAll()
{
	updateSummary();
	updateDataList();
	updateExtraList();
	updateChart();
}

void Coins::WidgetMain::updateDependentOnData()
{
	updateSummary();
	updateDataList();
	updateChart();
}

void Coins::WidgetMain::updateDependentOnExtra()
{
	updateSummary();
	updateDataList();
	updateExtraList();
	updateChart();
}

void Coins::WidgetMain::updateSummary()
{
	_widget_summary->update(_data_list, _extra_list);
}

void Coins::WidgetMain::updateDataList()
{
	_widget_data_list->update(_data_list, _extra_list);
}

void Coins::WidgetMain::updateExtraList()
{
	_widget_extra_list->update(_extra_list);
}

void Coins::WidgetMain::updateChart()
{
	_widget_chart->update(_data_list, _extra_list);
}
