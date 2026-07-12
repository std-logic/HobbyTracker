#pragma once

#include <gui/base/widgets/BaseWidgetControl.h>

class QPushButton;
class QComboBox;

namespace Base
{
class ButtonAdd;
class ButtonCollapse;
class ButtonExpand;
class ButtonShow;
}

namespace Flights
{

class WidgetControl : public Base::WidgetControl
{
	Q_OBJECT
public:
	explicit WidgetControl(QWidget* parent = nullptr);
	~WidgetControl() = default;

	void start() override;

signals:
	void showDataList(bool on);
	void addData();
	void collapseDataList();
	void expandDataList();
	void setDataListViewMode(int view_mode);

	void showChart(bool on);

private:
	void initWidgets();

private:
	Base::ButtonShow* _button_data_list = nullptr;
	Base::ButtonAdd* _button_add_data = nullptr;
	Base::ButtonCollapse* _button_collapse_data_list = nullptr;
	Base::ButtonExpand* _button_expand_data_list = nullptr;
	QComboBox* _combo_data_list_view_mode = nullptr;

	Base::ButtonShow* _button_chart = nullptr;
};

} // namespace Flights
