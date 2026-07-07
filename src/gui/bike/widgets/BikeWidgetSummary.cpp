#include "BikeWidgetSummary.h"
#include "../data/BikeDataList.h"

#include <common/Helper.h>

#include <QLabel>

Bike::WidgetSummary::WidgetSummary(QWidget* parent)
	: Base::WidgetSummary{parent}
{
	initWidgets();
}

void Bike::WidgetSummary::update(const DataList& list)
{
	auto summary = list.summary();

	_label_years->setText(Helper::yearString(summary.min_year, summary.max_year));

	_label_total_dist->setText(QString::number(summary.total_dist));

	_label_avg_dist->setText(QString::number(summary.avg_dist, 'f', 0));

	_label_total_time->setText(QString::number(summary.total_time));

	_label_avg_time->setText(QString::number(summary.avg_time, 'f', 0));
}

void Bike::WidgetSummary::initWidgets()
{
	addWidget(tr("Годы:"), _label_years = new QLabel(this));

	addWidget(tr("Пробег общий:"), _label_total_dist = new QLabel(this), 0);

	addWidget(tr("средний:"), _label_avg_dist = new QLabel(this));

	addWidget(tr("Время общее:"), _label_total_time = new QLabel(this), 0);

	addWidget(tr("среднее:"), _label_avg_time = new QLabel(this));

	addStretch();
}
