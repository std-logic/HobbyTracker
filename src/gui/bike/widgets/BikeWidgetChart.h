#pragma once

#include <gui/base/widgets/BaseWidgetChart.h>

namespace Bike
{

class DataList;

class WidgetChart : public Base::WidgetChart
{
	Q_OBJECT
public:
	explicit WidgetChart(QWidget* parent = nullptr);
	~WidgetChart() = default;

	void update(const DataList& list);

signals:

private:
	void showByDist(const DataList& list);
	void showByTime(const DataList& list);
};

} // namespace Bike
