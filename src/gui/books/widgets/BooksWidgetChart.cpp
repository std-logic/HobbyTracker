#include "BooksWidgetChart.h"
#include "../common/BooksCommon.h"
#include "../data/BooksDataList.h"

Books::WidgetChart::WidgetChart(QWidget* parent)
	: Base::WidgetChart{parent}
{
}

void Books::WidgetChart::update(const DataList& data_list)
{
	clearChart();
	switch (static_cast<ChartViewModes>(_view_mode)) {
		case ChartViewModes::ByDecades:		showByDecades(data_list);		break;
		case ChartViewModes::ByCenturies:	showByCenturies(data_list);		break;
		case ChartViewModes::ByRatings:		showByRatings(data_list);		break;
		default: return;
	}
}

void Books::WidgetChart::showByDecades(const DataList& data_list)
{
	chart()->setTitle(tr("Распределение по десятилетиям"));
	updateBars(data_list.numbersByYears(10, DataList::RangeTypes::LinearWithMin, 1800));
}

void Books::WidgetChart::showByCenturies(const DataList& data_list)
{
	chart()->setTitle(tr("Распределение по столетиям"));
	updateBars(data_list.numbersByYears(100));
}

void Books::WidgetChart::showByRatings(const DataList& data_list)
{
	chart()->setTitle(tr("Распределение по оценкам"));
	updateBars(data_list.numbersByRatings());
}
