#include "MusicWidgetSummary.h"
#include "../data/MusicDataList.h"

#include <common/Helper.h>

#include <QLabel>

Music::WidgetSummary::WidgetSummary(QWidget* parent)
	: Base::WidgetSummary{parent}
{
	initWidgets();
}

void Music::WidgetSummary::update(const DataList& data_list)
{
	auto summary = data_list.summary();

	_label_artists_num->setText(QString::number(summary.artists_num));

	_label_actives_num->setText(QString::number(summary.actives_num));

	_label_genres_num->setText(QString::number(summary.genres_num));

	_label_countries_num->setText(QString::number(summary.countries_num));

	_label_years->setText(Helper::yearString(summary.min_year, summary.max_year));
}

void Music::WidgetSummary::initWidgets()
{
	addWidget(tr("Групп:"), _label_artists_num);

	addWidget(tr("Активно:"), _label_actives_num);

	addWidget(tr("Жанров:"), _label_genres_num);

	addWidget(tr("Стран:"), _label_countries_num);

	addWidget(tr("Годы:"), _label_years);

	addStretch();
}
