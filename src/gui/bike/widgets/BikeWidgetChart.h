#pragma once

#include <gui/base/widgets/BaseWidgetChart.h>

namespace Bike
{

class DataList;
class TripList;

class WidgetChart : public Base::WidgetChart
{
	Q_OBJECT
public:
	explicit WidgetChart(QWidget* parent = nullptr);
	~WidgetChart() = default;

	void update(const DataList& list, const TripList& trip_list);

signals:

private:
	void showByDist(const DataList& list);
	void showByTime(const DataList& list);
	void showByTrips(const TripList& trip_list);
};

} // namespace Bike
