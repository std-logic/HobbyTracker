#include "MoviesWidgetSummary.h"
#include "../data/MoviesDataList.h"

#include <gui/base/data/BaseExtraList.h>

#include <common/Helper.h>
#include <common/Regions.h>

#include <QLabel>

Movies::WidgetSummary::WidgetSummary(QWidget* parent)
	: Base::WidgetSummary{parent}
{
	initWidgets();
}

void Movies::WidgetSummary::update(const DataList& data_list, const Base::ExtraList& extra_list)
{
	if (data_list.empty()) {
		clear();
		return;
	}

	auto synonyms = extra_list.getSynonyms(tr("[Синонимы для стран]"));
	auto summary = data_list.summary(synonyms, _favorites_only);

	_label_viewed_num->setText(QString::number(summary.viewed_num));
	_label_movies_num->setText(QString::number(summary.movies_num));
	_label_series_num->setText(QString::number(summary.series_num));
	_label_animation_num->setText(QString::number(summary.animation_num));
	_label_animation_series_num->setText(QString::number(summary.animation_series_num));
	_label_countries_num->setText(QString::number(summary.countries_num));
	_label_countries_num->setToolTip(Regions::progress(summary.list_of_countries));
	_label_years->setText(Helper::yearString(summary.min_year, summary.max_year));
	_label_rating->setText(QString::number(summary.rating, 'f', 1));
}

void Movies::WidgetSummary::setFavoritesOnly(Qt::CheckState state)
{
	bool favorites_only = (state == Qt::Checked);
	if (_favorites_only == favorites_only) { return; }
	_favorites_only = favorites_only;

	emit needUpdate();
}

void Movies::WidgetSummary::initWidgets()
{
	addWidget(tr("Всего:"), _label_viewed_num);
	addWidget(tr("Фильмов:"), _label_movies_num);
	addWidget(tr("Сериалов:"), _label_series_num);
	addWidget(tr("Мультфильмов:"), _label_animation_num);
	addWidget(tr("Мультсериалов:"), _label_animation_series_num);
	addWidget(tr("Стран:"), _label_countries_num);
	_label_countries_num->setToolTipDuration(1000000);
	addWidget(tr("Годы:"), _label_years);
	addWidget(tr("Оценки:"), _label_rating, 0);

	addStretch();
}
