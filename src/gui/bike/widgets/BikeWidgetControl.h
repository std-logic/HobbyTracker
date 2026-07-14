#pragma once

#include <gui/base/widgets/BaseWidgetControl.h>

namespace Base
{
class ButtonAdd;
class ButtonShow;
class ComboBox;
}

namespace Bike
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

	void showTripList(bool on);
	void addTrip();

	void showChart(bool on);
	void setChartViewMode(int view_mode);

private:
	void initWidgets();

private:
	Base::ButtonShow* _button_data_list = nullptr;
	Base::ButtonAdd* _button_add_data = nullptr;

	Base::ButtonShow* _button_trip_list = nullptr;
	Base::ButtonAdd* _button_add_trip = nullptr;

	Base::ButtonShow* _button_chart = nullptr;
	Base::ComboBox* _combo_chart_view_mode = nullptr;
};

} // namespace Bike
