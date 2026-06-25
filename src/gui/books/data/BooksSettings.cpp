#include "BooksSettings.h"
#include "BooksConverter.h"
#include "../common/BooksCommon.h"

#include <QSettings>
#include <QFile>

Books::Settings::Settings()
{
}

void Books::Settings::save() const
{
	QSettings settings(fullPath(SETTINGS_FILE_NAME), QSettings::IniFormat);

	_csv_settings.save(&settings);
}

void Books::Settings::load()
{
	QSettings settings(fullPath(SETTINGS_FILE_NAME), QSettings::IniFormat);

	// create settings file automatically if it doesn't exists (first run)
	if (!QFile::exists(settings.fileName())) {
		_csv_settings.setFileName(fullPath(DATA_FILE_NAME));
		save();
	}

	_csv_settings.load(&settings);
	_csv_settings.setHeader(Converter::getDefaultCsvHeader());
}
