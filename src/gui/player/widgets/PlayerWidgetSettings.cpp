#include "PlayerWidgetSettings.h"

#include <common/Global.h>

#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QFileDialog>

Player::WidgetSettings::WidgetSettings(const Settings& settings, QWidget* parent)
	: Base::WidgetSettings{parent}
	, _settings{settings}
{
	initWidgets();
	copySettingsToGui();
}

void Player::WidgetSettings::initWidgets()
{
	auto layout_dir = new QHBoxLayout();
	layout_dir->setContentsMargins(0, 0, 0, 0);
	layout_dir->setSpacing(Global::Sizes::default_spacing);

	_button_choose_default_dir =
			new QPushButton(QIcon::fromTheme(QIcon::ThemeIcon::FolderOpen), "", this);
	_button_choose_default_dir->setToolTip(tr("Выбрать директорию..."));
	_button_choose_default_dir->setFixedWidth(24);
	_button_choose_default_dir->setFocusPolicy(Qt::NoFocus);
	connect(_button_choose_default_dir, &QPushButton::clicked,
			this, &WidgetSettings::chooseDefaultDir);
	layout_dir->addWidget(_button_choose_default_dir);

	_edit_default_dir = new QLineEdit(this);
	layout_dir->addWidget(_edit_default_dir);

	addLayout(tr("Директория по умолчанию:"), layout_dir);
}

void Player::WidgetSettings::copySettingsToGui()
{
	_edit_default_dir->setText(_settings.defaultDir());
}

void Player::WidgetSettings::copyGuiToSettings()
{
	_settings.setDefaultDir(_edit_default_dir->text());
}

void Player::WidgetSettings::chooseDefaultDir()
{
	auto dir_name = QFileDialog::getExistingDirectory(
			this,
			tr("Выберите директорию по умолчанию"),
			_edit_default_dir->text());
	if (dir_name.isEmpty()) { return; }

	_edit_default_dir->setText(dir_name);
}

void Player::WidgetSettings::save()
{
	copyGuiToSettings();
	emit saveSettings(_settings);
}
