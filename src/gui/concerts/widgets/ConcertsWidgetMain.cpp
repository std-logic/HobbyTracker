#include "ConcertsWidgetMain.h"
#include "ConcertsWidgetControl.h"
#include "ConcertsWidgetSummary.h"
#include "ConcertsWidgetData.h"
#include "ConcertsWidgetDataList.h"
#include "ConcertsWidgetChart.h"
#include "ConcertsWidgetSettings.h"
#include "../common/ConcertsCommon.h"
#include "../data/ConcertsDataConverter.h"

#include <gui/base/data/BaseExtraConverter.h>
#include <gui/base/widgets/BaseWidgetExtra.h>
#include <gui/base/widgets/BaseWidgetExtraList.h>

#include <storage/Storage.h>
#include <storage/csv/CsvData.h>

Concerts::WidgetMain::WidgetMain(QWidget* parent)
	: Base::WidgetMain{parent}
{
	initWidgets();
	initConnections();
}

void Concerts::WidgetMain::start()
{
	_widget_control->start();

	_settings.load();
	readCsvData(_settings.csvSettings());
}

void Concerts::WidgetMain::initWidgets()
{
	addWidget(_widget_control = new WidgetControl(this), 0, Qt::AlignTop);
	addWidget(_widget_summary = new WidgetSummary(this), 1, Qt::AlignTop);
	addWidget(_widget_data_list = new WidgetDataList(this), 100);
	addWidget(_widget_extra_list = new Base::WidgetExtraList(this), 100);
	addWidget(_widget_chart = new WidgetChart(this), 100);
}

void Concerts::WidgetMain::initConnections()
{
	connect(_widget_control, &WidgetControl::showDataList,
			_widget_data_list, &WidgetDataList::setVisible);
	connect(_widget_control, &WidgetControl::collapseDataList,
			_widget_data_list, &WidgetDataList::collapseAll);
	connect(_widget_control, &WidgetControl::expandDataList,
			_widget_data_list, &WidgetDataList::expandAll);
	connect(_widget_control, &WidgetControl::setDataListViewMode,
			_widget_data_list, &WidgetDataList::setViewMode);
	connect(_widget_control, &WidgetControl::setFavoritesState,
			_widget_data_list, &WidgetDataList::setFavoritesState);

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

void Concerts::WidgetMain::showSettings()
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

void Concerts::WidgetMain::saveSettings(const Settings& settings)
{
	_settings = settings;
	_settings.save();
	emit showMessage(tr("Настройки сохранены"));
}

void Concerts::WidgetMain::readCsvData(const Csv::Settings& csv_settings)
{
	auto csv_data = Storage::readCsv(CsvFileData, csv_settings);
	_data_list = DataConverter::conv(csv_data);

	csv_data = Storage::readCsv(CsvFileExtra, csv_settings);
	_extra_list = Base::ExtraConverter::conv(csv_data);

	updateAll();
}

void Concerts::WidgetMain::saveCsvData()
{
	auto csv_data = DataConverter::conv(_data_list);
	auto write_data_ok = Storage::writeCsv(CsvFileData, _settings.csvSettings(), csv_data);

	csv_data = Base::ExtraConverter::conv(_extra_list);
	auto write_extra_ok = Storage::writeCsv(CsvFileExtra, _settings.csvSettings(), csv_data);

	if (write_data_ok && write_extra_ok) {
		_widget_control->highlightButtonSave(false);
		emit showMessage(tr("Данные сохранены"));
	} else {
		emit showMessage(tr("Ошибка записи в файл!"));
	}
}

void Concerts::WidgetMain::addData()
{
	showData(_data_list.size());
}

void Concerts::WidgetMain::editData(const QString& id)
{
	if (auto i = _data_list.findIndexById(id); i >= 0) {
		showData(i);
	}
}

void Concerts::WidgetMain::showData(size_t index)
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

void Concerts::WidgetMain::saveData(size_t index, const Data& data)
{
	if (_data_list.set(index, data)) {
		updateDependentOnData();
		_widget_control->highlightButtonSave(true);
	}
}

void Concerts::WidgetMain::deleteData(const QString& id)
{
	if (auto i = _data_list.findIndexById(id); i >= 0) {
		if (askDel(tr("Удалить концерт за %1?").arg(_data_list[i].date()))) {
			_data_list.del(i);
			updateDependentOnData();
			_widget_control->highlightButtonSave(true);
		}
	}
}

void Concerts::WidgetMain::addExtra()
{
	showExtra(_extra_list.size());
}

void Concerts::WidgetMain::editExtra(const QString& id)
{
	if (auto i = _extra_list.findIndexById(id); i >= 0) {
		showExtra(i);
	}
}

void Concerts::WidgetMain::showExtra(size_t index)
{
	if (!_widget_extra) {
		_widget_extra = new Base::WidgetExtra(index, _extra_list, this);
		_widget_extra->addSpecialGroup(
				tr("[Теги]"),
				tr("Перечисление через запятую тегов,\nкоторые ищутся в описаниях концертов"),
				tr("Общее название для концертов с данными тегами")
		);
		_widget_extra->addSpecialGroup(
				tr("[Синонимы для групп]"),
				tr("Перечисление через запятую групп,\nкоторые должны объединяться в одну"),
				tr("Общее название для вышеуказанных групп")
		);
		_widget_extra->addSpecialGroup(
				tr("[Синонимы для мест]"),
				tr("Перечисление через запятую мест,\nкоторые должны объединяться в одно"),
				tr("Общее название для вышеуказанных мест")
		);
		_widget_extra->addSpecialGroup(
				tr("[Избранные группы]"),
				tr("Если «Только избранные» включены, в режиме «По группам»\n"
				   "будут отображаться только те, что добавлены здесь"),
				""
		);
		_widget_extra->addSpecialGroup(
				tr("[Избранные места]"),
				tr("Если «Только избранные» включены, в режиме «По местам»\n"
				   "будут отображаться только те, что добавлены здесь"),
				""
		);
		connect(_widget_extra, &Base::WidgetExtra::showMessage,
				this, &WidgetMain::showMessage);
		connect(_widget_extra, &Base::WidgetExtra::saveExtra,
				this, &WidgetMain::saveExtra);
	}
	_widget_extra->open();
}

void Concerts::WidgetMain::saveExtra(size_t index, const Base::Extra& extra)
{
	if (_extra_list.set(index, extra)) {
		updateDependentOnExtra();
		_widget_control->highlightButtonSave(true);
	}
}

void Concerts::WidgetMain::deleteExtra(const QString& id)
{
	if (auto i = _extra_list.findIndexById(id); i >= 0) {
		if (askDel(tr("Удалить запись \"%1\"?").arg(_extra_list[i].title()))) {
			_extra_list.del(i);
			updateDependentOnExtra();
			_widget_control->highlightButtonSave(true);
		}
	}
}

void Concerts::WidgetMain::updateAll()
{
	updateSummary();
	updateDataList();
	updateExtraList();
	updateChart();
}

void Concerts::WidgetMain::updateDependentOnData()
{
	updateSummary();
	updateDataList();
	updateChart();
}

void Concerts::WidgetMain::updateDependentOnExtra()
{
	updateDataList();
	updateExtraList();
	updateChart();
}

void Concerts::WidgetMain::updateSummary()
{
	_widget_summary->update(_data_list);
}

void Concerts::WidgetMain::updateDataList()
{
	_widget_data_list->update(_data_list, _extra_list);
}

void Concerts::WidgetMain::updateExtraList()
{
	_widget_extra_list->update(_extra_list);
}

void Concerts::WidgetMain::updateChart()
{
	_widget_chart->update(_data_list, _extra_list);
}
