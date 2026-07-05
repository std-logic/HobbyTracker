#include "GamesWidgetSummary.h"
#include "../data/GamesDataList.h"

#include <common/Helper.h>

#include <QLabel>

Games::WidgetSummary::WidgetSummary(QWidget* parent)
	: Base::WidgetSummary{parent}
{
	initWidgets();
}

void Games::WidgetSummary::update(const DataList& list)
{
	auto summary = list.summary();

	_label_series_num->setText(QString::number(summary.series_num));

	_label_games_num->setText(QString::number(summary.games_num));

	_label_genres_num->setText(QString::number(summary.genres_num));

	_label_developers_num->setText(QString::number(summary.developers_num));

	_label_years->setText(Helper::yearString(summary.min_year, summary.max_year));

	_label_rating->setText(QString::number(summary.rating, 'f', 1));
}

void Games::WidgetSummary::initWidgets()
{
	addWidget(tr("Серий:"), _label_series_num = new QLabel(this));

	addWidget(tr("Игр:"), _label_games_num = new QLabel(this));

	addWidget(tr("Жанров:"), _label_genres_num = new QLabel(this));

	addWidget(tr("Разработчиков:"), _label_developers_num = new QLabel(this));

	addWidget(tr("Годы:"), _label_years = new QLabel(this));

	addWidget(tr("Средняя оценка:"), _label_rating = new QLabel(this));

	addStretch();
}
