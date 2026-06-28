#include "BooksWidgetMain.h"
#include "BooksWidgetControl.h"
#include "BooksWidgetSummary.h"
#include "BooksWidgetList.h"
#include "BooksWidgetStatistics.h"
#include "BooksWidgetSettings.h"
#include "../data/BooksConverter.h"

#include <storage/Storage.h>

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

	addWidget(_widget_summary = new WidgetSummary(this), 0, Qt::AlignTop);

	addWidget(_widget_list = new WidgetList(this));

	addWidget(_widget_statistics = new WidgetStatistics(this));
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

	connect(_widget_control, &WidgetControl::showStatistics,
			_widget_statistics, &WidgetList::setVisible);

	connect(_widget_control, &WidgetControl::showSettings,
			this, &WidgetMain::showSettings);

	connect(_widget_list, &WidgetList::needUpdate,
			this, &WidgetMain::updateList);
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
	_csv_data = Storage::readCsv(csv_settings);
	_data_list = Converter::conv(_csv_data.value());

	_widget_summary->update(_data_list.value());
	_widget_list->update(_data_list.value());
}

void Books::WidgetMain::updateList()
{
	if (_data_list.has_value()) {
		_widget_list->update(_data_list.value());
	}
}
