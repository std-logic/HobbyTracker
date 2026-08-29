#include "CoinsWidgetChart.h"
#include "../common/CoinsCommon.h"
#include "../data/CoinsDataList.h"

#include <gui/base/data/BaseExtraList.h>

Coins::WidgetChart::WidgetChart(QWidget* parent)
	: Base::WidgetChart{parent}
{
}

void Coins::WidgetChart::update(const DataList& data_list, const Base::ExtraList& extra_list)
{
	clearChart();
	switch (static_cast<ChartViewModes>(_view_mode)) {
		case ChartViewModes::ByCountries:	showByCountries(data_list, extra_list);		break;
		case ChartViewModes::ByRegions:		showByRegions(data_list, extra_list);		break;
		case ChartViewModes::ByDecades:		showByDecades(data_list);					break;
		case ChartViewModes::ByCenturies:	showByCenturies(data_list);					break;
		case ChartViewModes::ByDiameters:	showByDiameters(data_list);					break;
		default: return;
	}
}

void Coins::WidgetChart::showByCountries(const DataList& data_list, const Base::ExtraList& extra_list)
{
	chart()->setTitle(tr("Распределение по странам"));
	auto synonyms = extra_list.getSynonyms(tr("[Синонимы для стран]"));
	updateBars(data_list.numbersByCountries(10, synonyms));
}

void Coins::WidgetChart::showByRegions(const DataList& data_list, const Base::ExtraList& extra_list)
{
	chart()->setTitle(tr("Распределение по регионам"));
	auto synonyms = extra_list.getSynonyms(tr("[Синонимы для стран]"));
	updateBars(data_list.numbersByRegions(10, synonyms));
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

void Coins::WidgetChart::showByDiameters(const DataList& data_list)
{
	chart()->setTitle(tr("Распределение по диаметрам"));
	updateBars(data_list.numbersByDiameters());
}
