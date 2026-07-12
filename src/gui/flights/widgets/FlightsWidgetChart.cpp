#include "FlightsWidgetChart.h"
#include "../data/FlightsDataList.h"

Flights::WidgetChart::WidgetChart(QWidget* parent)
	: Base::WidgetChart{parent}
{
}

void Flights::WidgetChart::update(const DataList& data_list)
{
	clearChart();
	showByYears(data_list);
}

void Flights::WidgetChart::showByYears(const DataList& data_list)
{
	chart()->setTitle(tr("Полётов по годам"));
	updateBars(data_list.numbersByYears(1, DataList::RangeTypes::Linear));
}
