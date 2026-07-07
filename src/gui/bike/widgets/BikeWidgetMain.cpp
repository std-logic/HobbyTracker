#include "BikeWidgetMain.h"
#include "BikeWidgetControl.h"
#include "BikeWidgetSummary.h"
#include "BikeWidgetData.h"
#include "BikeWidgetDataList.h"
#include "BikeWidgetChart.h"
#include "BikeWidgetSettings.h"
#include "../common/BikeCommon.h"
#include "../data/BikeDataConverter.h"

#include <storage/Storage.h>
#include <storage/csv/CsvData.h>

#include <QMessageBox>

Bike::WidgetMain::WidgetMain(QWidget* parent)
	: Base::WidgetMain{parent}
{
	initWidgets();
	initConnections();
}

void Bike::WidgetMain::start()
{
	_widget_control->start();

	_settings.load();
	readCsvData(_settings.csvSettings());
}

void Bike::WidgetMain::initWidgets()
{
	addWidget(_widget_control = new WidgetControl(this), 0, Qt::AlignTop);

	addWidget(_widget_summary = new WidgetSummary(this), 1, Qt::AlignTop);

	addWidget(_widget_data_list = new WidgetDataList(this), 100);

	addWidget(_widget_chart = new WidgetChart(this), 100);
}

void Bike::WidgetMain::initConnections()
{
	connect(_widget_control, &WidgetControl::showDataList,
			_widget_data_list, &WidgetDataList::setVisible);

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

	connect(_widget_data_list, &WidgetDataList::needUpdate,
			this, &WidgetMain::updateDataList);
	connect(_widget_data_list, &WidgetDataList::editData,
			this, &WidgetMain::editData);
	connect(_widget_data_list, &WidgetDataList::deleteData,
			this, &WidgetMain::deleteData);

	connect(_widget_chart, &WidgetChart::needUpdate,
			this, &WidgetMain::updateChart);
}

void Bike::WidgetMain::showSettings()
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

void Bike::WidgetMain::saveSettings(const Settings& settings)
{
	_settings = settings;
	_settings.save();
	readCsvData(_settings.csvSettings());
}

void Bike::WidgetMain::readCsvData(const Csv::Settings& csv_settings)
{
	auto csv_data = Storage::readCsv(CsvFileData, csv_settings);
	_data_list = DataConverter::conv(csv_data);
	updateAll();
}

void Bike::WidgetMain::saveCsvData()
{
	auto csv_data = DataConverter::conv(_data_list);
	auto write_data_ok = Storage::writeCsv(CsvFileData, _settings.csvSettings(), csv_data);

	if (write_data_ok) {
		_widget_control->highlightButtonSave(false);
		emit showMessage(tr("Данные сохранены"));
	} else {
		emit showMessage(tr("Ошибка записи в файл!"));
	}
}

void Bike::WidgetMain::addData()
{
	showData(_data_list.size());
}

void Bike::WidgetMain::editData(const QString& id)
{
	if (auto i = _data_list.findIndexById(id); i >= 0) {
		showData(i);
	}
}

void Bike::WidgetMain::showData(size_t index)
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

void Bike::WidgetMain::saveData(size_t index, const Data& data)
{
	if (index < _data_list.size()) {
		if (_data_list[index] == data) { return; }
		_data_list[index] = data;
	} else {
		_data_list.add(data);
	}

	updateAll();
	_widget_control->highlightButtonSave(true);
}

void Bike::WidgetMain::deleteData(const QString& id)
{
	if (auto i = _data_list.findIndexById(id); i >= 0) {
		auto ans = QMessageBox::question(this, tr("Удаление данных"),
			tr("Удалить данные за %1-й год?").arg(_data_list[i].year()));

		if (ans == QMessageBox::Yes) {
			_data_list.del(i);
			updateAll();
			_widget_control->highlightButtonSave(true);
		}
	}
}

void Bike::WidgetMain::updateAll()
{
	updateSummary();
	updateDataList();
	updateChart();
}

void Bike::WidgetMain::updateSummary()
{
	_widget_summary->update(_data_list);
}

void Bike::WidgetMain::updateDataList()
{
	_widget_data_list->update(_data_list);
}

void Bike::WidgetMain::updateChart()
{
	_widget_chart->update(_data_list);
}
