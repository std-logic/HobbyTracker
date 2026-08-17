#include "ConcertsWidgetChart.h"
#include "../common/ConcertsCommon.h"
#include "../data/ConcertsDataList.h"

#include <gui/base/data/BaseExtraList.h>

Concerts::WidgetChart::WidgetChart(QWidget* parent)
	: Base::WidgetChart{parent}
{
}

void Concerts::WidgetChart::update(const DataList& data_list, const Base::ExtraList& extra_list)
{
	clearChart();
	switch (static_cast<ChartViewModes>(_view_mode)) {
		case ChartViewModes::ByYears:		showByYears(data_list);					break;
		case ChartViewModes::ByArtists:		showByArtists(data_list, extra_list);	break;
		case ChartViewModes::ByCountries:	showByCountries(data_list);				break;
		case ChartViewModes::ByCities:		showByCities(data_list);				break;
		case ChartViewModes::ByPlaces:		showByPlaces(data_list, extra_list);	break;
		default: return;
	}
}

void Concerts::WidgetChart::showByYears(const DataList& data_list)
{
	chart()->setTitle(tr("Распределение по годам"));
	updateBars(data_list.numbersByYears(1, DataList::RangeTypes::Linear));
}

void Concerts::WidgetChart::showByArtists(const DataList& data_list, const Base::ExtraList& extra_list)
{
	chart()->setTitle(tr("Распределение по группам"));
	auto synonyms = extra_list.getSynonyms(tr("[Синонимы для групп]"));
	updateBars(data_list.numbersByArtists(10, synonyms));
}

void Concerts::WidgetChart::showByCountries(const DataList& data_list)
{
	chart()->setTitle(tr("Распределение по странам"));
	updateBars(data_list.numbersByCountries(10));
}

void Concerts::WidgetChart::showByCities(const DataList& data_list)
{
	chart()->setTitle(tr("Распределение по городам"));
	updateBars(data_list.numbersByCities(10));
}

void Concerts::WidgetChart::showByPlaces(const DataList& data_list, const Base::ExtraList& extra_list)
{
	chart()->setTitle(tr("Распределение по местам"));
	auto synonyms = extra_list.getSynonyms(tr("[Синонимы для мест]"));
	updateBars(data_list.numbersByPlaces(10, synonyms));
}
