#include "GamesWidgetChart.h"
#include "../common/GamesCommon.h"
#include "../data/GamesDataList.h"

Games::WidgetChart::WidgetChart(QWidget* parent)
	: Base::WidgetChart{parent}
{
}

void Games::WidgetChart::update(const DataList& list)
{
	clearChart();
	switch (static_cast<ChartViewModes>(_view_mode)) {
		case ChartViewModes::ByYears:		showByYears(list);			break;
		case ChartViewModes::ByDecades:		showByDecades(list);		break;
		case ChartViewModes::ByRatings:		showByRatings(list);		break;
		default: return;
	}
}

void Games::WidgetChart::showByYears(const DataList& list)
{
	chart()->setTitle(tr("Распределение по годам"));
	updateBars(list.numbersByYears(1, DataList::RangeTypes::Linear));
}

void Games::WidgetChart::showByDecades(const DataList& list)
{
	chart()->setTitle(tr("Распределение по десятилетиям"));
	updateBars(list.numbersByYears(10, DataList::RangeTypes::Linear));
}

void Games::WidgetChart::showByRatings(const DataList& list)
{
	chart()->setTitle(tr("Распределение по оценкам"));
	updateBars(list.numbersByRatings());
}
