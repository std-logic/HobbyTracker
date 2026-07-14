#include "MusicWidgetChart.h"
#include "../data/MusicDataList.h"

Music::WidgetChart::WidgetChart(QWidget* parent)
	: Base::WidgetChart{parent}
{
}

void Music::WidgetChart::update(const DataList& data_list)
{
	clearChart();
	showByDecades(data_list);
}

void Music::WidgetChart::showByDecades(const DataList& data_list)
{
	chart()->setTitle(tr("Распределение по десятилетиям"));
	updateBars(data_list.numbersByYears(10, DataList::RangeTypes::LinearWithMin, 1960));
}
