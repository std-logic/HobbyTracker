#include "FlightsWidgetSummary.h"
#include "../data/FlightsDataList.h"

#include <common/Helper.h>

#include <QLabel>

Flights::WidgetSummary::WidgetSummary(QWidget* parent)
	: Base::WidgetSummary{parent}
{
	initWidgets();
}

void Flights::WidgetSummary::update(const DataList& data_list)
{
	auto summary = data_list.summary();

	_label_years->setText(Helper::yearString(summary.min_year, summary.max_year));

	_label_countries_num->setText(QString::number(summary.countries_num));

	_label_cities_num->setText(QString::number(summary.cities_num));

	_label_airports_num->setText(QString::number(summary.airports_num));

	_label_flights_num->setText(QString::number(summary.flights_num));
}

void Flights::WidgetSummary::initWidgets()
{
	addWidget(tr("Годы:"), _label_years = new QLabel(this));

	addWidget(tr("Стран:"), _label_countries_num = new QLabel(this));

	addWidget(tr("Городов:"), _label_cities_num = new QLabel(this));

	addWidget(tr("Аэропортов:"), _label_airports_num = new QLabel(this));

	addWidget(tr("Полётов:"), _label_flights_num = new QLabel(this));

	addStretch();
}
