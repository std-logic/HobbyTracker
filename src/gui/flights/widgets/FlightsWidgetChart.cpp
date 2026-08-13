#include "FlightsWidgetChart.h"
#include "../common/FlightsCommon.h"
#include "../data/FlightsDataList.h"

Flights::WidgetChart::WidgetChart(QWidget* parent)
	: Base::WidgetChart{parent}
{
}

void Flights::WidgetChart::update(const DataList& data_list)
{
	clearChart();
	switch (static_cast<ChartViewModes>(_view_mode)) {
		case ChartViewModes::ByFlights:		showByFlights(data_list);		break;
		case ChartViewModes::ByDist:		showByDist(data_list);			break;
		default: return;
	}
}

void Flights::WidgetChart::showByFlights(const DataList& data_list)
{
	chart()->setTitle(tr("Распределение полётов по годам"));
	updateBars(data_list.numbersByYears(1, DataList::RangeTypes::Linear));
}

void Flights::WidgetChart::showByDist(const DataList& data_list)
{
	chart()->setTitle(tr("Распределение километров по годам"));
	updateBars(data_list.distByYears());
}
