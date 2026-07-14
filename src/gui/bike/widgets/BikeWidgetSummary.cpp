#include "BikeWidgetSummary.h"
#include "../data/BikeDataList.h"
#include "../data/BikeTripList.h"

#include <common/Helper.h>

#include <QLabel>

Bike::WidgetSummary::WidgetSummary(QWidget* parent)
	: Base::WidgetSummary{parent}
{
	initWidgets();
}

void Bike::WidgetSummary::update(const DataList& data_list, const TripList& trip_list)
{
	auto data_summary = data_list.summary();

	_label_years->setText(Helper::yearString(data_summary.min_year, data_summary.max_year));

	_label_total_time->setText(QString::number(data_summary.total_time));

	_label_total_dist->setText(QString::number(data_summary.total_dist));

	auto trip_summary = trip_list.summary();

	_label_trips_num->setText(QString::number(trip_summary.trips_num));

	_label_trips_total_time->setText(QString::number(trip_summary.total_time));

	_label_trips_total_dist->setText(QString::number(trip_summary.total_dist));
}

void Bike::WidgetSummary::initWidgets()
{
	addWidget(tr("Годы:"), _label_years);

	addWidget(tr("Всего часов:"), _label_total_time);

	addWidget(tr("Всего километров:"), _label_total_dist);

	addWidget(tr("Велопоходов:"), _label_trips_num);

	addWidget(tr("Ночёвок:"), _label_trips_total_time);

	addWidget(tr("Километров:"), _label_trips_total_dist);

	addStretch();
}
