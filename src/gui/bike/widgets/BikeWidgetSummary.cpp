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

void Bike::WidgetSummary::update(const DataList& list, const TripList& trip_list)
{
	auto summary = list.summary();

	_label_years->setText(Helper::yearString(summary.min_year, summary.max_year));

	_label_total_dist->setText(QString::number(summary.total_dist));

	_label_total_time->setText(QString::number(summary.total_time));

	auto trip_summary = trip_list.summary();

	_label_trips_num->setText(QString::number(trip_summary.trips_num));

	_label_trips_total_dist->setText(QString::number(trip_summary.total_dist));

	_label_trips_total_time->setText(QString::number(trip_summary.total_time));
}

void Bike::WidgetSummary::initWidgets()
{
	addWidget(tr("Годы:"), _label_years = new QLabel(this));

	addWidget(tr("Всего километров:"), _label_total_dist = new QLabel(this));

	addWidget(tr("Всего часов:"), _label_total_time = new QLabel(this));

	addWidget(tr("Велопоходов:"), _label_trips_num = new QLabel(this));

	addWidget(tr("Километров:"), _label_trips_total_dist = new QLabel(this));

	addWidget(tr("Ночёвок:"), _label_trips_total_time = new QLabel(this));

	addStretch();
}
