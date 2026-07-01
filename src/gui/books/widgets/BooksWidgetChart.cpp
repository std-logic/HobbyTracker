#include "BooksWidgetChart.h"
#include "../common/BooksCommon.h"
#include "../data/BooksDataList.h"

Books::WidgetChart::WidgetChart(QWidget* parent)
	: Base::WidgetChart{parent}
{
}

void Books::WidgetChart::update(const DataList& list)
{
	clearChart();
	switch (static_cast<ChartViewModes>(_view_mode)) {
		case ChartViewModes::ByDecades:		showByDecades(list);		break;
		case ChartViewModes::ByCenturies:	showByCenturies(list);		break;
		case ChartViewModes::ByRatings:		showByRatings(list);		break;
		default: return;
	}
}

void Books::WidgetChart::showByDecades(const DataList& list)
{
	chart()->setTitle(tr("Распределение по десятилетиям"));
	updateBars(list.numberByYears(10, DataList::RangeTypes::LinearWithMin, 1800));
}

void Books::WidgetChart::showByCenturies(const DataList& list)
{
	chart()->setTitle(tr("Распределение по столетиям"));
	updateBars(list.numberByYears(100, DataList::RangeTypes::Linear));
}

void Books::WidgetChart::showByRatings(const DataList& list)
{
	chart()->setTitle(tr("Распределение по оценкам"));
	updateBars(list.numberByRatings());
}
