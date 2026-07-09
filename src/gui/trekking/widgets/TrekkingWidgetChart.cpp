#include "TrekkingWidgetChart.h"
#include "../data/TrekkingDataList.h"

Trekking::WidgetChart::WidgetChart(QWidget* parent)
	: Base::WidgetChart{parent}
{
}

void Trekking::WidgetChart::update(const DataList& data_list)
{
	clearChart();
	showByYears(data_list);
}

void Trekking::WidgetChart::showByYears(const DataList& data_list)
{
	chart()->setTitle(tr("Походов по годам"));
	updateBars(data_list.numbersByYears(1, DataList::RangeTypes::Linear));
}
