#include "BooksSettings.h"
#include "BooksDataConverter.h"
#include "../common/BooksCommon.h"

#include <common/Helper.h>
#include <gui/base/data/BaseExtraConverter.h>

#include <QSettings>

Books::Settings::Settings()
	: Base::Settings{settings_group_name}
{
}

void Books::Settings::save() const
{
	QSettings settings(Helper::stdPathSettings(), QSettings::IniFormat);

	settings.beginGroup(_group_name);

	_csv_settings.save(&settings, "csv");

	settings.endGroup();
}

void Books::Settings::load()
{
	QSettings settings(Helper::stdPathSettings(), QSettings::IniFormat);

	// create group automatically if it doesn't exists (first run)
	if (!settings.childGroups().contains(_group_name)) {
		_csv_settings.setFileName(CsvFileData, Helper::stdPath(csv_file_names[CsvFileData]));
		_csv_settings.setFileName(CsvFileExtra, Helper::stdPath(csv_file_names[CsvFileExtra]));
		save();
	}

	settings.beginGroup(_group_name);

	_csv_settings.load(&settings, "csv");
	_csv_settings.setHeader(CsvFileData, DataConverter::getDefaultCsvHeader());
	_csv_settings.setHeader(CsvFileExtra, Base::ExtraConverter::getDefaultCsvHeader());

	settings.endGroup();
}
