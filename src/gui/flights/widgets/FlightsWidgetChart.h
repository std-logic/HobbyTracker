#pragma once

#include <gui/base/widgets/BaseWidgetChart.h>

namespace Flights
{

class DataList;

class WidgetChart : public Base::WidgetChart
{
	Q_OBJECT
public:
	explicit WidgetChart(QWidget* parent = nullptr);
	~WidgetChart() = default;

	void update(const DataList& data_list);

signals:

private:
	void showByYears(const DataList& data_list);
};

} // namespace Flights
