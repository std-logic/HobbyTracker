#pragma once

#include "../data/PlayerSettings.h"

#include <gui/base/widgets/BaseWidgetSettings.h>

class QPushButton;
class QLineEdit;

namespace Player
{

class WidgetSettings : public Base::WidgetSettings
{
	Q_OBJECT
public:
	explicit WidgetSettings(const Settings& settings, QWidget* parent = nullptr);
	~WidgetSettings() = default;

signals:
	void saveSettings(const Settings& settings);

private:
	void initWidgets();

	void copySettingsToGui();
	void copyGuiToSettings();

private slots:
	void chooseDefaultDir();
	void save() override;

private:
	QPushButton* _button_choose_default_dir = nullptr;
	QLineEdit* _edit_default_dir = nullptr;

	Settings _settings;
};

} // namespace Player
