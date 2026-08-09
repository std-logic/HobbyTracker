#include "CoinsSettings.h"
#include "CoinsDataConverter.h"
#include "../common/CoinsCommon.h"

#include <common/Helper.h>
#include <gui/base/data/BaseExtraConverter.h>

#include <QSettings>

Coins::Settings::Settings()
	: Base::Settings{settings_group_name}
{
}

void Coins::Settings::checkFirstRun()
{
	QSettings settings(Helper::stdPathSettings(), QSettings::IniFormat);

	if (!settings.childGroups().contains(_group_name)) {
		for (int i = 0; i < NumOfCsvFiles; ++i) {
			_csv_settings.setFileName(i, Helper::stdPath(csv_file_names[i]));
		}
		save();
	}
}

void Coins::Settings::save() const
{
	QSettings settings(Helper::stdPathSettings(), QSettings::IniFormat);
	settings.beginGroup(_group_name);

	_csv_settings.save(&settings, "csv");

	settings.endGroup();
}

void Coins::Settings::load()
{
	checkFirstRun();

	QSettings settings(Helper::stdPathSettings(), QSettings::IniFormat);
	settings.beginGroup(_group_name);

	_csv_settings.load(&settings, "csv");
	_csv_settings.setHeader(CsvFileData, DataConverter::getDefaultCsvHeader());
	_csv_settings.setHeader(CsvFileExtra, Base::ExtraConverter::getDefaultCsvHeader());

	settings.endGroup();
}
