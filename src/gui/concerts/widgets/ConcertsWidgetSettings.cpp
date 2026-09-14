#include "ConcertsWidgetSettings.h"

#include <gui/base/widgets/BaseWidgetCsvSettings.h>
#include <gui/base/widgets/BaseWidgetFileEdit.h>

Concerts::WidgetSettings::WidgetSettings(const Settings& settings, QWidget* parent)
	: Base::WidgetSettings{parent}
	, _settings{settings}
{
	initWidgets();
	copySettingsToGui();
}

void Concerts::WidgetSettings::initWidgets()
{
	addWidget(_widget_csv_settings = new Base::WidgetCsvSettings(_settings.csvSettings(), this));
	connect(_widget_csv_settings, &Base::WidgetCsvSettings::readCsvData,
			this, &WidgetSettings::readCsvData);

	add(tr("Директория с фото:"), _widget_photo_dir);
	_widget_photo_dir->setMode(Base::WidgetFileEdit::ChooseMode::Dir);
}

void Concerts::WidgetSettings::copySettingsToGui()
{
	_widget_photo_dir->setText(_settings.photoDir());
}

void Concerts::WidgetSettings::copyGuiToSettings()
{
	_settings.setCsvSettings(_widget_csv_settings->getSettings());
	_settings.setPhotoDir(_widget_photo_dir->text());
}

void Concerts::WidgetSettings::save()
{
	copyGuiToSettings();
	emit saveSettings(_settings);
}
