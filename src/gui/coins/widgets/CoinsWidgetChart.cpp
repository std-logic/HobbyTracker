#include "CoinsWidgetChart.h"
#include "../common/CoinsCommon.h"
#include "../data/CoinsDataList.h"

Coins::WidgetChart::WidgetChart(QWidget* parent)
	: Base::WidgetChart{parent}
{
}

void Coins::WidgetChart::update(const DataList& data_list)
{
	clearChart();
	switch (static_cast<ChartViewModes>(_view_mode)) {
		case ChartViewModes::ByDecades:		showByDecades(data_list);		break;
		case ChartViewModes::ByCenturies:	showByCenturies(data_list);		break;
		default: return;
	}
}

void Coins::WidgetChart::showByDecades(const DataList& data_list)
{
	chart()->setTitle(tr("Распределение по десятилетиям"));
	updateBars(data_list.numbersByYears(10, DataList::RangeTypes::LinearWithMin, 1900));
}

void Coins::WidgetChart::showByCenturies(const DataList& data_list)
{
	chart()->setTitle(tr("Распределение по столетиям"));
	updateBars(data_list.numbersByYears(100, DataList::RangeTypes::Linear));
}
