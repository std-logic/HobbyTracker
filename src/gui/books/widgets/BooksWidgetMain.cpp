#include "BooksWidgetMain.h"
#include "BooksWidgetControl.h"
#include "BooksWidgetSummary.h"
#include "BooksWidgetList.h"
#include "BooksWidgetChart.h"
#include "BooksWidgetSettings.h"
#include "BooksWidgetData.h"
#include "../data/BooksConverter.h"

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

	addWidget(_widget_list = new WidgetList(this), 100);

	addWidget(_widget_chart = new WidgetChart(this), 100);
}

void Books::WidgetMain::initConnections()
{
	connect(_widget_control, &WidgetControl::showList,
			_widget_list, &WidgetList::setVisible);
	connect(_widget_control, &WidgetControl::collapseList,
			_widget_list, &WidgetList::collapseAll);
	connect(_widget_control, &WidgetControl::expandList,
			_widget_list, &WidgetList::expandAll);
	connect(_widget_control, &WidgetControl::setListViewMode,
			_widget_list, &WidgetList::setViewMode);

	connect(_widget_control, &WidgetControl::showChart,
			_widget_chart, &WidgetChart::setVisible);
	connect(_widget_control, &WidgetControl::setChartViewMode,
			_widget_chart, &WidgetChart::setViewMode);

	connect(_widget_control, &WidgetControl::saveCsvData,
			this, &WidgetMain::saveCsvData);
	connect(_widget_control, &WidgetControl::addData,
			this, &WidgetMain::addData);
	connect(_widget_control, &WidgetControl::showSettings,
			this, &WidgetMain::showSettings);

	connect(this, &WidgetMain::highlightButtonSave,
			_widget_control, &WidgetControl::highlightButtonSave);

	connect(_widget_list, &WidgetList::needUpdate,
			this, &WidgetMain::updateList);
	connect(_widget_list, &WidgetList::editData,
			this, &WidgetMain::editData);
	connect(_widget_list, &WidgetList::deleteData,
			this, &WidgetMain::deleteData);

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
	auto csv_data = Storage::readCsv(csv_settings);
	_data_list = Converter::conv(csv_data);

	updateAll();
}

void Books::WidgetMain::saveCsvData()
{
	auto csv_data = Converter::conv(_data_list.value());
	auto write_ok = Storage::writeCsv(_settings.csvSettings(), csv_data);

	if (write_ok) {
		emit highlightButtonSave(false);
		emit showMessage(tr("Данные сохранены в файл %1")
						 .arg(_settings.csvSettings().fileName()));
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
	for (size_t i = 0; i < _data_list.value().size(); ++i) {
		if (id == _data_list.value()[i].id()) {
			showData(i);
			break;
		}
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
	for (size_t i = 0; i < _data_list.value().size(); ++i) {
		if (id == _data_list.value()[i].id()) {
			deleteDataAtIndex(i);
			break;
		}
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

void Books::WidgetMain::updateAll()
{
	updateSummary();
	updateList();
	updateChart();
}

void Books::WidgetMain::updateSummary()
{
	if (_data_list.has_value()) { _widget_summary->update(_data_list.value()); }
}

void Books::WidgetMain::updateList()
{
	if (_data_list.has_value()) { _widget_list->update(_data_list.value()); }
}

void Books::WidgetMain::updateChart()
{
	if (_data_list.has_value()) { _widget_chart->update(_data_list.value()); }
}
