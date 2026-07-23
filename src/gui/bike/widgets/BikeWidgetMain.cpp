#include "BikeWidgetMain.h"
#include "BikeWidgetControl.h"
#include "BikeWidgetSummary.h"
#include "BikeWidgetData.h"
#include "BikeWidgetDataList.h"
#include "BikeWidgetTrip.h"
#include "BikeWidgetTripList.h"
#include "BikeWidgetChart.h"
#include "BikeWidgetSettings.h"
#include "../common/BikeCommon.h"
#include "../data/BikeDataConverter.h"
#include "../data/BikeTripConverter.h"

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

	addWidget(_widget_trip_list = new WidgetTripList(this), 100);

	addWidget(_widget_chart = new WidgetChart(this), 100);
}

void Bike::WidgetMain::initConnections()
{
	connect(_widget_control, &WidgetControl::showDataList,
			_widget_data_list, &WidgetDataList::setVisible);

	connect(_widget_control, &WidgetControl::showTripList,
			_widget_trip_list, &WidgetTripList::setVisible);

	connect(_widget_control, &WidgetControl::showChart,
			_widget_chart, &WidgetChart::setVisible);
	connect(_widget_control, &WidgetControl::setChartViewMode,
			_widget_chart, &WidgetChart::setViewMode);

	connect(_widget_control, &WidgetControl::saveCsvData,
			this, &WidgetMain::saveCsvData);
	connect(_widget_control, &WidgetControl::addData,
			this, &WidgetMain::addData);
	connect(_widget_control, &WidgetControl::addTrip,
			this, &WidgetMain::addTrip);
	connect(_widget_control, &WidgetControl::showSettings,
			this, &WidgetMain::showSettings);

	connect(_widget_data_list, &WidgetDataList::needUpdate,
			this, &WidgetMain::updateDataList);
	connect(_widget_data_list, &WidgetDataList::editData,
			this, &WidgetMain::editData);
	connect(_widget_data_list, &WidgetDataList::deleteData,
			this, &WidgetMain::deleteData);

	connect(_widget_trip_list, &WidgetTripList::needUpdate,
			this, &WidgetMain::updateTripList);
	connect(_widget_trip_list, &WidgetTripList::editData,
			this, &WidgetMain::editTrip);
	connect(_widget_trip_list, &WidgetTripList::deleteData,
			this, &WidgetMain::deleteTrip);

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
	emit showMessage(tr("Настройки сохранены"));
	readCsvData(_settings.csvSettings());
}

void Bike::WidgetMain::readCsvData(const Csv::Settings& csv_settings)
{
	auto csv_data = Storage::readCsv(CsvFileData, csv_settings);
	_data_list = DataConverter::conv(csv_data);

	csv_data = Storage::readCsv(CsvFileTrip, csv_settings);
	_trip_list = TripConverter::conv(csv_data);

	updateAll();
}

void Bike::WidgetMain::saveCsvData()
{
	auto csv_data = DataConverter::conv(_data_list);
	auto write_data_ok = Storage::writeCsv(CsvFileData, _settings.csvSettings(), csv_data);

	csv_data = TripConverter::conv(_trip_list);
	auto write_trip_ok = Storage::writeCsv(CsvFileTrip, _settings.csvSettings(), csv_data);

	if (write_data_ok && write_trip_ok) {
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

	updateDependentOnData();
	_widget_control->highlightButtonSave(true);
}

void Bike::WidgetMain::deleteData(const QString& id)
{
	if (auto i = _data_list.findIndexById(id); i >= 0) {
		auto ans = QMessageBox::question(this, tr("Удаление данных"),
			tr("Удалить данные за %1-й год?").arg(_data_list[i].year()));

		if (ans == QMessageBox::Yes) {
			_data_list.del(i);
			updateDependentOnData();
			_widget_control->highlightButtonSave(true);
		}
	}
}

void Bike::WidgetMain::addTrip()
{
	showTrip(_trip_list.size());
}

void Bike::WidgetMain::editTrip(const QString& id)
{
	if (auto i = _trip_list.findIndexById(id); i >= 0) {
		showTrip(i);
	}
}

void Bike::WidgetMain::showTrip(size_t index)
{
	if (!_widget_trip) {
		_widget_trip = new WidgetTrip(index, _trip_list, this);
		connect(_widget_trip, &WidgetTrip::showMessage,
				this, &WidgetMain::showMessage);
		connect(_widget_trip, &WidgetTrip::saveData,
				this, &WidgetMain::saveTrip);
	}
	_widget_trip->open();
}

void Bike::WidgetMain::saveTrip(size_t index, const Trip& trip)
{
	if (index < _trip_list.size()) {
		if (_trip_list[index] == trip) { return; }
		_trip_list[index] = trip;
	} else {
		_trip_list.add(trip);
	}

	updateDependentOnTrip();
	_widget_control->highlightButtonSave(true);
}

void Bike::WidgetMain::deleteTrip(const QString& id)
{
	if (auto i = _trip_list.findIndexById(id); i >= 0) {
		auto ans = QMessageBox::question(this, tr("Удаление данных"),
			tr("Удалить велопоход за %1?").arg(_trip_list[i].dates()));

		if (ans == QMessageBox::Yes) {
			_trip_list.del(i);
			updateDependentOnTrip();
			_widget_control->highlightButtonSave(true);
		}
	}
}

void Bike::WidgetMain::updateAll()
{
	updateSummary();
	updateDataList();
	updateTripList();
	updateChart();
}

void Bike::WidgetMain::updateDependentOnData()
{
	updateSummary();
	updateDataList();
	updateChart();
}

void Bike::WidgetMain::updateDependentOnTrip()
{
	updateSummary();
	updateTripList();
	updateChart();
}

void Bike::WidgetMain::updateSummary()
{
	_widget_summary->update(_data_list, _trip_list);
}

void Bike::WidgetMain::updateDataList()
{
	_widget_data_list->update(_data_list);
}

void Bike::WidgetMain::updateTripList()
{
	_widget_trip_list->update(_trip_list);
}

void Bike::WidgetMain::updateChart()
{
	_widget_chart->update(_data_list, _trip_list);
}
