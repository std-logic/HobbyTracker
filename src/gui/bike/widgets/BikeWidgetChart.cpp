#include "BikeWidgetChart.h"
#include "../common/BikeCommon.h"
#include "../data/BikeDataList.h"
#include "../data/BikeTripList.h"

Bike::WidgetChart::WidgetChart(QWidget* parent)
	: Base::WidgetChart{parent}
{
}

void Bike::WidgetChart::update(const DataList& data_list, const TripList& trip_list)
{
	clearChart();
	switch (static_cast<ChartViewModes>(_view_mode)) {
		case ChartViewModes::ByDist:		showByDist(data_list);		break;
		case ChartViewModes::ByTime:		showByTime(data_list);		break;
		case ChartViewModes::ByTrips:		showByTrips(trip_list);		break;
		default: return;
	}
}

void Bike::WidgetChart::showByDist(const DataList& data_list)
{
	chart()->setTitle(tr("Километров по годам"));
	updateBars(data_list.distByYears());
}

void Bike::WidgetChart::showByTime(const DataList& data_list)
{
	chart()->setTitle(tr("Часов по годам"));
	updateBars(data_list.timeByYears());
}

void Bike::WidgetChart::showByTrips(const TripList& trip_list)
{
	chart()->setTitle(tr("Велопоходов по годам"));
	updateBars(trip_list.numbersByYears(1, TripList::RangeTypes::Linear));
}
