#include "MusicWidgetChart.h"
#include "../common/MusicCommon.h"
#include "../data/MusicDataList.h"

Music::WidgetChart::WidgetChart(QWidget* parent)
	: Base::WidgetChart{parent}
{
}

void Music::WidgetChart::update(const DataList& data_list)
{
	clearChart();
	switch (static_cast<ChartViewModes>(_view_mode)) {
		case ChartViewModes::ByGenres:		showByGenres(data_list);		break;
		case ChartViewModes::ByCountries:	showByCountries(data_list);		break;
		case ChartViewModes::ByDecades:		showByDecades(data_list);		break;
		default: return;
	}
}

void Music::WidgetChart::showByGenres(const DataList& data_list)
{
	chart()->setTitle(tr("Распределение по жанрам"));
	updateBars(data_list.numbersByGenres(10));
}

void Music::WidgetChart::showByCountries(const DataList& data_list)
{
	chart()->setTitle(tr("Распределение по странам"));
	updateBars(data_list.numbersByCountries(10));
}

void Music::WidgetChart::showByDecades(const DataList& data_list)
{
	chart()->setTitle(tr("Распределение по десятилетиям"));
	updateBars(data_list.numbersByYears(10, DataList::RangeTypes::LinearWithMin, 1960));
}
