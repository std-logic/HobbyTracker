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
		case ChartViewModes::ByViewDates:	showByViewDates(data_list);		break;
		case ChartViewModes::ByYears:		showByYears(data_list);			break;
		case ChartViewModes::ByDecades:		showByDecades(data_list);		break;
		case ChartViewModes::ByRatings:		showByRatings(data_list);		break;
		default: return;
	}
}

void Movies::WidgetChart::setFavoritesOnly(Qt::CheckState state)
{
	bool favorites_only = (state == Qt::Checked);
	if (_favorites_only == favorites_only) { return; }
	_favorites_only = favorites_only;

	emit needUpdate();
}

void Movies::WidgetChart::showByViewDates(const DataList& data_list)
{
	chart()->setTitle(tr("Распределение по годам просмотра"));
	updateBars(data_list.numbersByViewDates(_favorites_only));
}

void Movies::WidgetChart::showByYears(const DataList& data_list)
{
	chart()->setTitle(tr("Распределение по годам"));
	updateBars(data_list.numbersByYears(1, DataList::RangeTypes::Linear, 0, 0, _favorites_only));
}

void Movies::WidgetChart::showByDecades(const DataList& data_list)
{
	chart()->setTitle(tr("Распределение по десятилетиям"));
	updateBars(data_list.numbersByYears(10, DataList::RangeTypes::Linear, 0, 0, _favorites_only));
}

void Movies::WidgetChart::showByRatings(const DataList& data_list)
{
	chart()->setTitle(tr("Распределение по оценкам"));
	updateBars(data_list.numbersByRatings(_favorites_only));
}
