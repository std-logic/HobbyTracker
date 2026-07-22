#include "PlayerSettings.h"
#include "../common/PlayerCommon.h"

#include <common/Helper.h>

#include <QSettings>

Player::Settings::Settings()
	: Base::Settings{settings_group_name}
{
}

void Player::Settings::checkFirstRun()
{
	QSettings settings(Helper::stdPathSettings(), QSettings::IniFormat);

	if (!settings.childGroups().contains(_group_name)) {
		save();
	}
}

void Player::Settings::save() const
{
	QSettings settings(Helper::stdPathSettings(), QSettings::IniFormat);
	settings.beginGroup(_group_name);

	settings.setValue("default_dir", _default_dir);

	settings.endGroup();
}

void Player::Settings::load()
{
	checkFirstRun();

	QSettings settings(Helper::stdPathSettings(), QSettings::IniFormat);
	settings.beginGroup(_group_name);

	_default_dir = settings.value("default_dir").toString();

	settings.endGroup();
}
