#include "MoviesWidgetChart.h"
#include "../common/MoviesCommon.h"
#include "../data/MoviesDataList.h"

Movies::WidgetChart::WidgetChart(QWidget* parent)
	: Base::WidgetChart{parent}
{
}

void Movies::WidgetChart::update(const DataList& data_list)
{
	clearChart();
	switch (static_cast<ChartViewModes>(_view_mode)) {
		case ChartViewModes::ByYears:		showByYears(data_list);			break;
		case ChartViewModes::ByDecades:		showByDecades(data_list);		break;
		case ChartViewModes::ByRatings:		showByRatings(data_list);		break;
		case ChartViewModes::ByViewDates:	showByViewDates(data_list);		break;
		default: return;
	}
}

void Movies::WidgetChart::showByYears(const DataList& data_list)
{
	chart()->setTitle(tr("Распределение по годам"));
	updateBars(data_list.numbersByYears(1, DataList::RangeTypes::Linear));
}

void Movies::WidgetChart::showByDecades(const DataList& data_list)
{
	chart()->setTitle(tr("Распределение по десятилетиям"));
	updateBars(data_list.numbersByYears(10, DataList::RangeTypes::Linear));
}

void Movies::WidgetChart::showByRatings(const DataList& data_list)
{
	chart()->setTitle(tr("Распределение по оценкам"));
	updateBars(data_list.numbersByRatings());
}

void Movies::WidgetChart::showByViewDates(const DataList& data_list)
{
	chart()->setTitle(tr("Распределение по годам просмотра"));
	updateBars(data_list.numbersByViewDates());
}
