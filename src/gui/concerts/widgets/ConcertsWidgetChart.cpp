#include "ConcertsWidgetChart.h"
#include "../data/ConcertsDataList.h"

Concerts::WidgetChart::WidgetChart(QWidget* parent)
	: Base::WidgetChart{parent}
{
}

void Concerts::WidgetChart::update(const DataList& data_list)
{
	clearChart();
	showByYears(data_list);
}

void Concerts::WidgetChart::showByYears(const DataList& data_list)
{
	chart()->setTitle(tr("Распределение по годам"));
	updateBars(data_list.numbersByYears(1, DataList::RangeTypes::Linear));
}
