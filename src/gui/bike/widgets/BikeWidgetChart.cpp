#include "BikeWidgetChart.h"
#include "../common/BikeCommon.h"
#include "../data/BikeDataList.h"

Bike::WidgetChart::WidgetChart(QWidget* parent)
	: Base::WidgetChart{parent}
{
}

void Bike::WidgetChart::update(const DataList& list)
{
	clearChart();
	switch (static_cast<ChartViewModes>(_view_mode)) {
		case ChartViewModes::ByDist:		showByDist(list);		break;
		case ChartViewModes::ByTime:		showByTime(list);		break;
		default: return;
	}
}

void Bike::WidgetChart::showByDist(const DataList& list)
{
	chart()->setTitle(tr("Пробеги по годам"));
	updateBars(list.distByYears());
}

void Bike::WidgetChart::showByTime(const DataList& list)
{
	chart()->setTitle(tr("Время по годам"));
	updateBars(list.timeByYears());
}
