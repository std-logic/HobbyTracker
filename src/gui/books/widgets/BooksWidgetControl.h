#pragma once

#include <gui/base/widgets/BaseWidgetControl.h>

class QPushButton;
class QComboBox;

namespace Base
{
class ButtonAdd;
class ButtonCollapse;
class ButtonExpand;
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
	void saveCsvData();

	void showList(bool on);
	void addData();
	void collapseList();
	void expandList();
	void setListViewMode(int view_mode);

	void showChart(bool on);
	void setChartViewMode(int view_mode);

	void showSettings();

private:
	void initWidgets();

private:
	Base::ButtonSave* _button_save = nullptr;

	Base::ButtonShow* _button_list = nullptr;
	Base::ButtonAdd* _button_add_data = nullptr;
	Base::ButtonCollapse* _button_collapse_list = nullptr;
	Base::ButtonExpand* _button_expand_list = nullptr;
	QComboBox* _combo_list_view_mode = nullptr;

	Base::ButtonShow* _button_chart = nullptr;
	QComboBox* _combo_chart_view_mode = nullptr;

	Base::ButtonSettings* _button_settings = nullptr;
};

} // namespace Books
