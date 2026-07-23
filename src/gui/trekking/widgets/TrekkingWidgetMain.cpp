#include "TrekkingWidgetMain.h"
#include "TrekkingWidgetControl.h"
#include "TrekkingWidgetSummary.h"
#include "TrekkingWidgetData.h"
#include "TrekkingWidgetDataList.h"
#include "TrekkingWidgetChart.h"
#include "TrekkingWidgetSettings.h"
#include "../common/TrekkingCommon.h"
#include "../data/TrekkingDataConverter.h"

#include <storage/Storage.h>
#include <storage/csv/CsvData.h>

#include <QMessageBox>

Trekking::WidgetMain::WidgetMain(QWidget* parent)
	: Base::WidgetMain{parent}
{
	initWidgets();
	initConnections();
}

void Trekking::WidgetMain::start()
{
	_widget_control->start();

	_settings.load();
	readCsvData(_settings.csvSettings());
}

void Trekking::WidgetMain::initWidgets()
{
	addWidget(_widget_control = new WidgetControl(this), 0, Qt::AlignTop);

	addWidget(_widget_summary = new WidgetSummary(this), 1, Qt::AlignTop);

	addWidget(_widget_data_list = new WidgetDataList(this), 100);

	addWidget(_widget_chart = new WidgetChart(this), 100);
}

void Trekking::WidgetMain::initConnections()
{
	connect(_widget_control, &WidgetControl::showDataList,
			_widget_data_list, &WidgetDataList::setVisible);
	connect(_widget_control, &WidgetControl::collapseDataList,
			_widget_data_list, &WidgetDataList::collapseAll);
	connect(_widget_control, &WidgetControl::expandDataList,
			_widget_data_list, &WidgetDataList::expandAll);
	connect(_widget_control, &WidgetControl::setDataListViewMode,
			_widget_data_list, &WidgetDataList::setViewMode);

	connect(_widget_control, &WidgetControl::showChart,
			_widget_chart, &WidgetChart::setVisible);

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

void Trekking::WidgetMain::showSettings()
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

void Trekking::WidgetMain::saveSettings(const Settings& settings)
{
	_settings = settings;
	_settings.save();
	emit showMessage(tr("Настройки сохранены"));
	readCsvData(_settings.csvSettings());
}

void Trekking::WidgetMain::readCsvData(const Csv::Settings& csv_settings)
{
	auto csv_data = Storage::readCsv(CsvFileData, csv_settings);
	_data_list = DataConverter::conv(csv_data);

	updateAll();
}

void Trekking::WidgetMain::saveCsvData()
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

void Trekking::WidgetMain::addData()
{
	showData(_data_list.size());
}

void Trekking::WidgetMain::editData(const QString& id)
{
	if (auto i = _data_list.findIndexById(id); i >= 0) {
		showData(i);
	}
}

void Trekking::WidgetMain::showData(size_t index)
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

void Trekking::WidgetMain::saveData(size_t index, const Data& data)
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

void Trekking::WidgetMain::deleteData(const QString& id)
{
	if (auto i = _data_list.findIndexById(id); i >= 0) {
		auto ans = QMessageBox::question(this, tr("Удаление данных"),
			tr("Удалить поход за %1?").arg(_data_list[i].dates()));

		if (ans == QMessageBox::Yes) {
			_data_list.del(i);
			updateAll();
			_widget_control->highlightButtonSave(true);
		}
	}
}

void Trekking::WidgetMain::updateAll()
{
	updateSummary();
	updateDataList();
	updateChart();
}

void Trekking::WidgetMain::updateSummary()
{
	_widget_summary->update(_data_list);
}

void Trekking::WidgetMain::updateDataList()
{
	_widget_data_list->update(_data_list);
}

void Trekking::WidgetMain::updateChart()
{
	_widget_chart->update(_data_list);
}
