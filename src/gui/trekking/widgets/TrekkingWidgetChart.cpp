#include "TrekkingWidgetChart.h"
#include "../common/TrekkingCommon.h"
#include "../data/TrekkingDataList.h"

Trekking::WidgetChart::WidgetChart(QWidget* parent)
	: Base::WidgetChart{parent}
{
}

void Trekking::WidgetChart::update(const DataList& data_list)
{
	clearChart();
	switch (static_cast<ChartViewModes>(_view_mode)) {
		case ChartViewModes::ByYears:		showByYears(data_list);			break;
		case ChartViewModes::ByCountries:	showByCountries(data_list);		break;
		default: return;
	}
}

void Trekking::WidgetChart::showByYears(const DataList& data_list)
{
	chart()->setTitle(tr("Распределение по годам"));
	updateBars(data_list.numbersByYears(1, DataList::RangeTypes::Linear));
}

void Trekking::WidgetChart::showByCountries(const DataList& data_list)
{
	chart()->setTitle(tr("Распределение по странам"));
	updateBars(data_list.numbersByCountries(10));
}
