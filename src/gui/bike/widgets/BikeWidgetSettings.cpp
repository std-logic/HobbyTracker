#include "BikeWidgetSettings.h"

Bike::WidgetSettings::WidgetSettings(const Settings& settings, QWidget* parent)
	: Base::WidgetSettings{parent}
	, _settings{settings}
{
	initWidgets();
}

void Bike::WidgetSettings::initWidgets()
{
	addWidget(_widget_csv_settings = new Base::WidgetCsvSettings(_settings.csvSettings(), this));
	connect(_widget_csv_settings, &Base::WidgetCsvSettings::readCsvData,
			this, &WidgetSettings::readCsvData);
}

void Bike::WidgetSettings::copyGuiToSettings()
{
	_settings.setCsvSettings(_widget_csv_settings->getSettings());
}

void Bike::WidgetSettings::save()
{
	copyGuiToSettings();
	emit saveSettings(_settings);
}
