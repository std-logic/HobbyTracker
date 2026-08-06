#include "ConcertsWidgetSummary.h"
#include "../data/ConcertsDataList.h"

#include <common/Helper.h>

#include <QLabel>

Concerts::WidgetSummary::WidgetSummary(QWidget* parent)
	: Base::WidgetSummary{parent}
{
	initWidgets();
}

void Concerts::WidgetSummary::update(const DataList& data_list)
{
	if (data_list.empty()) {
		clear();
		return;
	}

	auto summary = data_list.summary();

	_label_years->setText(Helper::yearString(summary.min_year, summary.max_year));
	_label_countries_num->setText(QString::number(summary.countries_num));
	_label_cities_num->setText(QString::number(summary.cities_num));
	_label_places_num->setText(QString::number(summary.places_num));
	_label_artists_num->setText(QString::number(summary.artists_num));
	_label_concerts_num->setText(QString::number(summary.concerts_num));
}

void Concerts::WidgetSummary::initWidgets()
{
	addWidget(tr("Годы:"), _label_years);
	addWidget(tr("Стран:"), _label_countries_num);
	addWidget(tr("Городов:"), _label_cities_num);
	addWidget(tr("Мест:"), _label_places_num);
	addWidget(tr("Групп:"), _label_artists_num);
	addWidget(tr("Концертов:"), _label_concerts_num, 0);

	addStretch();
}
