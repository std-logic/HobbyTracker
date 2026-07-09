#include "TrekkingWidgetSummary.h"
#include "../data/TrekkingDataList.h"

#include <common/Helper.h>

#include <QLabel>

Trekking::WidgetSummary::WidgetSummary(QWidget* parent)
	: Base::WidgetSummary{parent}
{
	initWidgets();
}

void Trekking::WidgetSummary::update(const DataList& data_list)
{
	auto summary = data_list.summary();

	_label_years->setText(Helper::yearString(summary.min_year, summary.max_year));

	_label_tracks_num->setText(QString::number(summary.tracks_num));

	_label_total_time->setText(QString::number(summary.total_time));

	_label_total_dist->setText(QString::number(summary.total_dist));

	_label_highest_peak->setText(QString::number(summary.highest_peak));
}

void Trekking::WidgetSummary::initWidgets()
{
	addWidget(tr("Годы:"), _label_years = new QLabel(this));

	addWidget(tr("Походов:"), _label_tracks_num = new QLabel(this));

	addWidget(tr("Ночёвок:"), _label_total_time = new QLabel(this));

	addWidget(tr("Километров:"), _label_total_dist = new QLabel(this));

	addWidget(tr("Высшая точка:"), _label_highest_peak = new QLabel(this));

	addStretch();
}
