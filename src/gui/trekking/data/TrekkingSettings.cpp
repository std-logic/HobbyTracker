#include "TrekkingSettings.h"
#include "TrekkingDataConverter.h"
#include "../common/TrekkingCommon.h"

#include <common/Helper.h>

#include <QSettings>

Trekking::Settings::Settings()
	: Base::Settings{settings_group_name}
{
}

void Trekking::Settings::checkFirstRun()
{
	QSettings settings(Helper::stdPathSettings(), QSettings::IniFormat);

	if (!settings.childGroups().contains(_group_name)) {
		for (int i = 0; i < NumOfCsvFiles; ++i) {
			_csv_settings.setFileName(i, Helper::stdPath(csv_file_names[i]));
		}
		save();
	}
}

void Trekking::Settings::save() const
{
	QSettings settings(Helper::stdPathSettings(), QSettings::IniFormat);
	settings.beginGroup(_group_name);

	_csv_settings.save(&settings, "csv");

	settings.endGroup();
}

void Trekking::Settings::load()
{
	checkFirstRun();

	QSettings settings(Helper::stdPathSettings(), QSettings::IniFormat);
	settings.beginGroup(_group_name);

	_csv_settings.load(&settings, "csv");
	_csv_settings.setHeader(CsvFileData, DataConverter::getDefaultCsvHeader());

	settings.endGroup();
}
