#include "PlayerWidgetSummary.h"
#include "../data/PlayerLibrary.h"

#include <common/Helper.h>

#include <QLabel>

Player::WidgetSummary::WidgetSummary(QWidget* parent)
	: Base::WidgetSummary{parent}
{
	initWidgets();
}

void Player::WidgetSummary::update(const Library& library)
{
	if (library.empty()) {
		clear();
		return;
	}

	auto summary = library.summary();

	_label_title->setText(summary.title);
	_label_years->setText(Helper::yearString(summary.min_year, summary.max_year));
	_label_artists_num->setText(QString::number(summary.artists_num));
	_label_albums_num->setText(QString::number(summary.albums_num));
	_label_tracks_num->setText(QString::number(summary.tracks_num));
	_label_genres_num->setText(QString::number(summary.genres_num));
	_label_play_count->setText(QString::number(summary.play_count));
}

void Player::WidgetSummary::update(const std::vector<Library>& libraries)
{
	if (libraries.empty()) {
		clear();
		return;
	}

	_label_title->setText(QStringLiteral("%1 → %2 (%3)")
			.arg(libraries.front().titleOnlyDate(), libraries.back().titleOnlyDate())
			.arg(libraries.size())
	);
	_label_years->setText("-");
	_label_artists_num->setText("-");
	_label_albums_num->setText("-");
	_label_tracks_num->setText("-");
	_label_genres_num->setText("-");
	_label_play_count->setText("-");
}

void Player::WidgetSummary::initWidgets()
{
	addWidget(tr("Файлы:"), _label_title);
	addWidget(tr("Годы:"), _label_years);
	addWidget(tr("Групп:"), _label_artists_num);
	addWidget(tr("Альбомов:"), _label_albums_num);
	addWidget(tr("Треков:"), _label_tracks_num);
	addWidget(tr("Жанров:"), _label_genres_num);
	addWidget(tr("Прослушиваний:"), _label_play_count);

	addStretch();
}
