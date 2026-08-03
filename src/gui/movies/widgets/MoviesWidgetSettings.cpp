#include "MoviesWidgetSettings.h"

Movies::WidgetSettings::WidgetSettings(const Settings& settings, QWidget* parent)
	: Base::WidgetSettings{parent}
	, _settings{settings}
{
	initWidgets();
}

void Movies::WidgetSettings::initWidgets()
{
	addWidget(_widget_csv_settings = new Base::WidgetCsvSettings(_settings.csvSettings(), this));
	connect(_widget_csv_settings, &Base::WidgetCsvSettings::readCsvData,
			this, &WidgetSettings::readCsvData);
}

void Movies::WidgetSettings::copyGuiToSettings()
{
	_settings.setCsvSettings(_widget_csv_settings->getSettings());
}

void Movies::WidgetSettings::save()
{
	copyGuiToSettings();
	emit saveSettings(_settings);
}
