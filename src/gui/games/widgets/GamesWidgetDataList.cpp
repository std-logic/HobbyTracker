#include "GamesWidgetDataList.h"
#include "../common/GamesCommon.h"
#include "../data/GamesDataList.h"

#include <gui/base/widgets/BaseWidgetTreeItem.h>

Games::WidgetDataList::WidgetDataList(QWidget* parent)
	: Base::WidgetTree{parent}
{
}

void Games::WidgetDataList::update(const DataList& list)
{
	clear();
	switch (static_cast<DataListViewModes>(_view_mode)) {
		case DataListViewModes::BySeries:		showBySeries(list);			break;
		case DataListViewModes::ByGenres:		showByGenres(list);			break;
		case DataListViewModes::ByDevelopers:	showByDevelopers(list);		break;
		case DataListViewModes::ByYears:		showByYears(list);			break;
		case DataListViewModes::ByDecades:		showByDecades(list);		break;
		case DataListViewModes::ByRatings:		showByRatings(list);		break;
		case DataListViewModes::Simple:			showSimple(list);			break;
		default: return;
	}
}

void Games::WidgetDataList::showBySeries(const DataList& list)
{
	enum Columns {CLMN_TITLE, CLMN_COUNT, CLMN_GENRE, CLMN_DEVELOPER, CLMN_YEAR, CLMN_RATING};
	initColumns({tr("Серия / Название"), tr("К-во"), tr("Жанр"), tr("Разработчик"), tr("Год"), tr("Оценка")},
				{WIDTH_TITLE, WIDTH_COUNT, WIDTH_GENRE, WIDTH_DEVELOPER, WIDTH_YEAR, WIDTH_RATING});
	initSorting(CLMN_TITLE);

	auto games_by_series = list.gamesBySeries();

	for (const auto& [series, games] : games_by_series) {
		auto item_series = new Base::WidgetTreeItem(this, Global::Colors::tree_level_1);
		item_series->setText(CLMN_TITLE, series);
		item_series->setNumb(CLMN_COUNT, games.size());
		item_series->setText(CLMN_YEAR, DataList::yearString(games));

		for (const auto game : games) {
			auto item_game = new Base::WidgetTreeItem(item_series);
			item_game->setText(CLMN_TITLE, game->title());
			item_game->setToolTip(CLMN_TITLE, game->summaryString());
			item_game->setText(CLMN_GENRE, game->genre());
			item_game->setText(CLMN_DEVELOPER, game->developer());
			item_game->setText(CLMN_YEAR, game->yearString());
			item_game->setRating(CLMN_RATING, game->rating());
			item_game->setId(game->id());
		}
	}
}

void Games::WidgetDataList::showByGenres(const DataList& list)
{
	enum Columns {CLMN_TITLE, CLMN_COUNT, CLMN_DEVELOPER, CLMN_YEAR, CLMN_RATING};
	initColumns({tr("Жанр / Название"), tr("К-во"), tr("Разработчик"), tr("Год"), tr("Оценка")},
				{WIDTH_TITLE, WIDTH_COUNT, WIDTH_DEVELOPER, WIDTH_YEAR, WIDTH_RATING});
	initSorting(CLMN_TITLE);

	auto games_by_genres = list.gamesByGenres();

	for (const auto& [genre, games] : games_by_genres) {
		auto item_genre = new Base::WidgetTreeItem(this, Global::Colors::tree_level_1);
		item_genre->setText(CLMN_TITLE, genre);
		item_genre->setNumb(CLMN_COUNT, games.size());
		item_genre->setText(CLMN_YEAR, DataList::yearString(games));

		for (const auto game : games) {
			auto item_game = new Base::WidgetTreeItem(item_genre);
			item_game->setText(CLMN_TITLE, game->title());
			item_game->setToolTip(CLMN_TITLE, game->summaryString());
			item_game->setText(CLMN_DEVELOPER, game->developer());
			item_game->setText(CLMN_YEAR, game->yearString());
			item_game->setRating(CLMN_RATING, game->rating());
			item_game->setId(game->id());
		}
	}
}

void Games::WidgetDataList::showByDevelopers(const DataList& list)
{
	enum Columns {CLMN_TITLE, CLMN_COUNT, CLMN_GENRE, CLMN_YEAR, CLMN_RATING};
	initColumns({tr("Разработчик / Название"), tr("К-во"), tr("Жанр"), tr("Год"), tr("Оценка")},
				{WIDTH_TITLE, WIDTH_COUNT, WIDTH_GENRE, WIDTH_YEAR, WIDTH_RATING});
	initSorting(CLMN_TITLE);

	auto games_by_developers = list.gamesByDevelopers();

	for (const auto& [developer, games] : games_by_developers) {
		auto item_developer = new Base::WidgetTreeItem(this, Global::Colors::tree_level_1);
		item_developer->setText(CLMN_TITLE, developer);
		item_developer->setNumb(CLMN_COUNT, games.size());
		item_developer->setText(CLMN_YEAR, DataList::yearString(games));

		for (const auto game : games) {
			auto item_game = new Base::WidgetTreeItem(item_developer);
			item_game->setText(CLMN_TITLE, game->title());
			item_game->setToolTip(CLMN_TITLE, game->summaryString());
			item_game->setText(CLMN_GENRE, game->genre());
			item_game->setText(CLMN_YEAR, game->yearString());
			item_game->setRating(CLMN_RATING, game->rating());
			item_game->setId(game->id());
		}
	}
}

void Games::WidgetDataList::showByYears(const DataList& list)
{
	enum Columns {CLMN_TITLE, CLMN_COUNT, CLMN_GENRE, CLMN_DEVELOPER, CLMN_RATING};
	initColumns({tr("Год / Название"), tr("К-во"), tr("Жанр"), tr("Разработчик"), tr("Оценка")},
				{WIDTH_TITLE, WIDTH_COUNT, WIDTH_GENRE, WIDTH_DEVELOPER, WIDTH_RATING});
	initSorting(CLMN_TITLE);

	auto games_by_years = list.gamesByYears(1);

	for (const auto& [year, games] : games_by_years) {
		auto item_year = new Base::WidgetTreeItem(this, Global::Colors::tree_level_1);
		item_year->setText(CLMN_TITLE, year);
		item_year->setNumb(CLMN_COUNT, games.size());

		for (const auto game : games) {
			auto item_game = new Base::WidgetTreeItem(item_year);
			item_game->setText(CLMN_TITLE, game->title());
			item_game->setToolTip(CLMN_TITLE, game->summaryString());
			item_game->setText(CLMN_GENRE, game->genre());
			item_game->setText(CLMN_DEVELOPER, game->developer());
			item_game->setRating(CLMN_RATING, game->rating());
			item_game->setId(game->id());
		}
	}
}

void Games::WidgetDataList::showByDecades(const DataList& list)
{
	enum Columns {CLMN_TITLE, CLMN_COUNT, CLMN_GENRE, CLMN_DEVELOPER, CLMN_YEAR, CLMN_RATING};
	initColumns({tr("Десятилетие / Название"), tr("К-во"), tr("Жанр"), tr("Разработчик"), tr("Год"), tr("Оценка")},
				{WIDTH_TITLE, WIDTH_COUNT, WIDTH_GENRE, WIDTH_DEVELOPER, WIDTH_YEAR, WIDTH_RATING});
	initSorting(CLMN_TITLE);

	auto games_by_years = list.gamesByYears(10);

	for (const auto& [decade, games] : games_by_years) {
		auto item_decade = new Base::WidgetTreeItem(this, Global::Colors::tree_level_1);
		item_decade->setText(CLMN_TITLE, decade);
		item_decade->setNumb(CLMN_COUNT, games.size());
		item_decade->setText(CLMN_YEAR, DataList::yearString(games));

		for (const auto game : games) {
			auto item_game = new Base::WidgetTreeItem(item_decade);
			item_game->setText(CLMN_TITLE, game->title());
			item_game->setToolTip(CLMN_TITLE, game->summaryString());
			item_game->setText(CLMN_GENRE, game->genre());
			item_game->setText(CLMN_DEVELOPER, game->developer());
			item_game->setText(CLMN_YEAR, game->yearString());
			item_game->setRating(CLMN_RATING, game->rating());
			item_game->setId(game->id());
		}
	}
}

void Games::WidgetDataList::showByRatings(const DataList& list)
{
	enum Columns {CLMN_TITLE, CLMN_COUNT, CLMN_GENRE, CLMN_DEVELOPER, CLMN_YEAR};
	initColumns({tr("Оценка / Название"), tr("К-во"), tr("Жанр"), tr("Разработчик"), tr("Год")},
				{WIDTH_TITLE, WIDTH_COUNT, WIDTH_GENRE, WIDTH_DEVELOPER, WIDTH_YEAR});
	initSorting(CLMN_TITLE);

	auto games_by_ratings = list.gamesByRatings();

	for (const auto& [rating, games] : games_by_ratings) {
		auto item_rating = new Base::WidgetTreeItem(this, Helper::ratingColor(rating));
		item_rating->setNumb(CLMN_TITLE, rating);
		item_rating->setNumb(CLMN_COUNT, games.size());
		item_rating->setText(CLMN_YEAR, DataList::yearString(games));

		for (const auto game : games) {
			auto item_game = new Base::WidgetTreeItem(item_rating);
			item_game->setText(CLMN_TITLE, game->title());
			item_game->setToolTip(CLMN_TITLE, game->summaryString());
			item_game->setText(CLMN_GENRE, game->genre());
			item_game->setText(CLMN_DEVELOPER, game->developer());
			item_game->setText(CLMN_YEAR, game->yearString());
			item_game->setId(game->id());
		}
	}
}

void Games::WidgetDataList::showSimple(const DataList& list)
{
	enum Columns {CLMN_TITLE, CLMN_GENRE, CLMN_DEVELOPER, CLMN_YEAR, CLMN_RATING};
	initColumns({tr("Название"), tr("Жанр"), tr("Разработчик"), tr("Год"), tr("Оценка")},
				{WIDTH_TITLE, WIDTH_GENRE, WIDTH_DEVELOPER, WIDTH_YEAR, WIDTH_RATING});
	initSorting(CLMN_TITLE);

	for (const auto& book : list) {
		auto item_book = new Base::WidgetTreeItem(this);
		item_book->setText(CLMN_TITLE, book.title());
		item_book->setToolTip(CLMN_TITLE, book.summaryString());
		item_book->setText(CLMN_GENRE, book.genre());
		item_book->setText(CLMN_DEVELOPER, book.developer());
		item_book->setText(CLMN_YEAR, book.yearString());
		item_book->setRating(CLMN_RATING, book.rating());
		item_book->setId(book.id());
	}
}
