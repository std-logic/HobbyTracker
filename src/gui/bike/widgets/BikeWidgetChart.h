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

	void update(const DataList& data_list, const TripList& trip_list);

signals:

private:
	void showByDist(const DataList& data_list);
	void showByTime(const DataList& data_list);
	void showByTrips(const TripList& trip_list);
};

} // namespace Bike
