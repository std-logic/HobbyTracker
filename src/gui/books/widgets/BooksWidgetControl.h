#pragma once

#include <gui/base/widgets/BaseWidgetControl.h>

class QPushButton;
class QComboBox;

namespace Base
{
class ButtonSave;
class ButtonSettings;
class ButtonShow;
}

namespace Books
{

class WidgetControl : public Base::WidgetControl
{
	Q_OBJECT
public:
	explicit WidgetControl(QWidget* parent = nullptr);
	~WidgetControl() = default;

	void start() override;

signals:
	void showList(bool on);
	void listModeChanged(int view_mode);

	void showStatistics(bool on);

private:
	void initGui();

private:
	Base::ButtonSave* _button_save = nullptr;

	Base::ButtonShow* _button_list = nullptr;
	QComboBox* _combo_list_mode = nullptr;

	Base::ButtonShow* _button_statistics = nullptr;

	Base::ButtonSettings* _button_settings = nullptr;
};

} // namespace Books
