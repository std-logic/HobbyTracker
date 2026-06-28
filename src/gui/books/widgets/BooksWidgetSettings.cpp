#include "BooksWidgetSettings.h"

Books::WidgetSettings::WidgetSettings(const Settings& settings, QWidget* parent)
	: Base::WidgetSettings{parent}
	, _settings{settings}
{
	initWidgets();
}

void Books::WidgetSettings::initWidgets()
{
	addWidget(_widget_csv_settings = new Base::WidgetCsvSettings(_settings.csvSettings(), this));
	connect(_widget_csv_settings, &Base::WidgetCsvSettings::readCsvData,
			this, &WidgetSettings::readCsvData);

	addStandardButtons();
}

void Books::WidgetSettings::save()
{
	_settings.setCsvSettings(_widget_csv_settings->getSettings());

	emit saveSettings(_settings);
}
