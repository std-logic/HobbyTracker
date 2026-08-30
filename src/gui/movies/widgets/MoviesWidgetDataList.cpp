#include "MoviesWidgetDataList.h"
#include "../common/MoviesCommon.h"
#include "../data/MoviesDataList.h"

#include <gui/base/data/BaseExtraList.h>
#include <gui/base/widgets/BaseWidgetTreeItem.h>

#include <common/Regions.h>

Movies::WidgetDataList::WidgetDataList(QWidget* parent)
	: Base::WidgetTree{parent}
{
}

void Movies::WidgetDataList::update(const DataList& data_list, const Base::ExtraList& extra_list)
{
	clear();
	setRootIsDecorated(static_cast<DataListViewModes>(_view_mode) != DataListViewModes::Simple);
	switch (static_cast<DataListViewModes>(_view_mode)) {
		case DataListViewModes::Simple:			showSimple(data_list);						break;
		case DataListViewModes::ByKinds:		showByKinds(data_list);						break;
		case DataListViewModes::ByGenres:		showByGenres(data_list);					break;
		case DataListViewModes::ByCountries:	showByCountries(data_list, extra_list);		break;
		case DataListViewModes::ByRegions:		showByRegions(data_list, extra_list);		break;
		case DataListViewModes::ByYears:		showByYears(data_list);						break;
		case DataListViewModes::ByDecades:		showByDecades(data_list);					break;
		case DataListViewModes::ByDirectors:	showByDirectors(data_list);					break;
		case DataListViewModes::ByWriters:		showByWriters(data_list);					break;
		case DataListViewModes::ByActors:		showByActors(data_list);					break;
		case DataListViewModes::ByRatings:		showByRatings(data_list);					break;
		default: return;
	}
}

void Movies::WidgetDataList::setFavoritesOnly(Qt::CheckState state)
{
	bool favorites_only = (state == Qt::Checked);
	if (_favorites_only == favorites_only) { return; }
	_favorites_only = favorites_only;

	emit needUpdate();
}

void Movies::WidgetDataList::showSimple(const DataList& data_list)
{
	enum Columns {CLMN_VIEW_DATE, CLMN_TITLE, CLMN_GENRES, CLMN_COUNTRIES,
				  CLMN_DIRECTORS, CLMN_ACTORS, CLMN_YEAR, CLMN_RATING};
	initColumns({tr("Дата"), tr("Название"), tr("Жанр"), tr("Страна"),
				 tr("Режиссёр"), tr("Актёры"), tr("Год"), tr("Оценка")},
				{WIDTH_VIEW_DATE_SMALL, WIDTH_TITLE, WIDTH_GENRES, WIDTH_COUNTRIES,
				 WIDTH_DIRECTORS, WIDTH_ACTORS, WIDTH_YEAR, WIDTH_RATING});
	initSorting(CLMN_VIEW_DATE, Qt::DescendingOrder);

	for (const auto& movie : data_list) {
		if (_favorites_only && !movie.isFavorite()) { continue; }
		auto item_movie = new Base::WidgetTreeItem(this);
		item_movie->setText(CLMN_VIEW_DATE, movie.viewDateWithoutSeconds());
		item_movie->setText(CLMN_TITLE, movie.title());
		item_movie->setText(CLMN_GENRES, movie.genresToString());
		item_movie->setText(CLMN_COUNTRIES, movie.countriesToString());
		item_movie->setText(CLMN_DIRECTORS, movie.directorsToString());
		item_movie->setText(CLMN_ACTORS, movie.actorsToString());
		item_movie->setText(CLMN_YEAR, movie.yearString());
		item_movie->setRating(CLMN_RATING, movie.rating());
		item_movie->setToolTipEverywhere(movie.summaryString());
		item_movie->setId(movie.id());
	}
}

void Movies::WidgetDataList::showByKinds(const DataList& data_list)
{
	enum Columns {CLMN_VIEW_DATE, CLMN_COUNT, CLMN_TITLE, CLMN_GENRES, CLMN_COUNTRIES,
				  CLMN_DIRECTORS, CLMN_ACTORS, CLMN_YEAR, CLMN_RATING};
	initColumns({tr("Тип / Дата"), tr("К-во"), tr("Название"), tr("Жанр"), tr("Страна"),
				 tr("Режиссёр"), tr("Актёры"), tr("Год"), tr("Оценка")},
				{WIDTH_VIEW_DATE_MEDIUM, WIDTH_COUNT, WIDTH_TITLE, WIDTH_GENRES, WIDTH_COUNTRIES,
				 WIDTH_DIRECTORS, WIDTH_ACTORS, WIDTH_YEAR, WIDTH_RATING});
	initSorting(CLMN_VIEW_DATE, Qt::DescendingOrder, true);

	auto movies_by_kinds = data_list.moviesByKinds(_favorites_only);

	for (const auto& [kind, movies] : movies_by_kinds) {
		auto item_kind = new Base::WidgetTreeItem(this, Global::Colors::tree_level_1);
		item_kind->setText(CLMN_VIEW_DATE, Helper::startWithCapital(kind));
		item_kind->setNumb(CLMN_COUNT, movies.size());
		item_kind->setText(CLMN_YEAR, Helper::yearString(movies));

		for (const auto movie : movies) {
			auto item_movie = new Base::WidgetTreeItem(item_kind);
			item_movie->setText(CLMN_VIEW_DATE, movie->viewDateWithoutSeconds());
			item_movie->setText(CLMN_TITLE, movie->title());
			item_movie->setText(CLMN_GENRES, movie->genresToString());
			item_movie->setText(CLMN_COUNTRIES, movie->countriesToString());
			item_movie->setText(CLMN_DIRECTORS, movie->directorsToString());
			item_movie->setText(CLMN_ACTORS, movie->actorsToString());
			item_movie->setText(CLMN_YEAR, movie->yearString());
			item_movie->setRating(CLMN_RATING, movie->rating());
			item_movie->setToolTipEverywhere(movie->summaryString());
			item_movie->setId(movie->id());
		}
	}
}

void Movies::WidgetDataList::showByGenres(const DataList& data_list)
{
	enum Columns {CLMN_VIEW_DATE, CLMN_COUNT, CLMN_TITLE, CLMN_GENRES, CLMN_COUNTRIES,
				  CLMN_DIRECTORS, CLMN_ACTORS, CLMN_YEAR, CLMN_RATING};
	initColumns({tr("Жанр / Дата"), tr("К-во"), tr("Название"), tr("Жанр"), tr("Страна"),
				 tr("Режиссёр"), tr("Актёры"), tr("Год"), tr("Оценка")},
				{WIDTH_VIEW_DATE_MEDIUM, WIDTH_COUNT, WIDTH_TITLE, WIDTH_GENRES, WIDTH_COUNTRIES,
				 WIDTH_DIRECTORS, WIDTH_ACTORS, WIDTH_YEAR, WIDTH_RATING});
	initSorting(CLMN_COUNT, Qt::DescendingOrder, true);

	auto movies_by_genres = data_list.moviesByGenres(_favorites_only);

	for (const auto& [genre, movies] : movies_by_genres) {
		if (genre.isEmpty() || genre.front().isDigit() ||
			(!_favorites_only && (movies.size() < 10))) { continue; }
		auto item_genre = new Base::WidgetTreeItem(this, Global::Colors::tree_level_1);
		item_genre->setText(CLMN_VIEW_DATE, Helper::startWithCapital(genre));
		item_genre->setNumb(CLMN_COUNT, movies.size());
		item_genre->setText(CLMN_YEAR, Helper::yearString(movies));

		for (const auto movie : movies) {
			auto item_movie = new Base::WidgetTreeItem(item_genre);
			item_movie->setText(CLMN_VIEW_DATE, movie->viewDateWithoutSeconds());
			item_movie->setText(CLMN_TITLE, movie->title());
			item_movie->setText(CLMN_GENRES, movie->genresToString());
			item_movie->setText(CLMN_COUNTRIES, movie->countriesToString());
			item_movie->setText(CLMN_DIRECTORS, movie->directorsToString());
			item_movie->setText(CLMN_ACTORS, movie->actorsToString());
			item_movie->setText(CLMN_YEAR, movie->yearString());
			item_movie->setRating(CLMN_RATING, movie->rating());
			item_movie->setToolTipEverywhere(movie->summaryString());
			item_movie->setId(movie->id());
		}
	}
}

void Movies::WidgetDataList::showByCountries(const DataList& data_list, const Base::ExtraList& extra_list)
{
	enum Columns {CLMN_VIEW_DATE, CLMN_COUNT, CLMN_TITLE, CLMN_GENRES, CLMN_COUNTRIES,
				  CLMN_DIRECTORS, CLMN_ACTORS, CLMN_YEAR, CLMN_RATING};
	initColumns({tr("Страна / Дата"), tr("К-во"), tr("Название"), tr("Жанр"), tr("Страна"),
				 tr("Режиссёр"), tr("Актёры"), tr("Год"), tr("Оценка")},
				{WIDTH_VIEW_DATE_MEDIUM, WIDTH_COUNT, WIDTH_TITLE, WIDTH_GENRES, WIDTH_COUNTRIES,
				 WIDTH_DIRECTORS, WIDTH_ACTORS, WIDTH_YEAR, WIDTH_RATING});
	initSorting(CLMN_COUNT, Qt::DescendingOrder, true);

	auto synonyms = extra_list.getSynonyms(tr("[Синонимы для стран]"));
	auto movies_by_countries = data_list.moviesByCountries(synonyms, _favorites_only);

	for (const auto& [country, movies] : movies_by_countries) {
		auto item_country = new Base::WidgetTreeItem(this, Global::Colors::tree_level_1);
		item_country->setText(CLMN_VIEW_DATE, country);
		item_country->setNumb(CLMN_COUNT, movies.size());
		item_country->setText(CLMN_YEAR, Helper::yearString(movies));

		for (const auto movie : movies) {
			auto item_movie = new Base::WidgetTreeItem(item_country);
			item_movie->setText(CLMN_VIEW_DATE, movie->viewDateWithoutSeconds());
			item_movie->setText(CLMN_TITLE, movie->title());
			item_movie->setText(CLMN_GENRES, movie->genresToString());
			item_movie->setText(CLMN_COUNTRIES, movie->countriesToString());
			item_movie->setText(CLMN_DIRECTORS, movie->directorsToString());
			item_movie->setText(CLMN_ACTORS, movie->actorsToString());
			item_movie->setText(CLMN_YEAR, movie->yearString());
			item_movie->setRating(CLMN_RATING, movie->rating());
			item_movie->setToolTipEverywhere(movie->summaryString());
			item_movie->setId(movie->id());
		}
	}
}

void Movies::WidgetDataList::showByRegions(const DataList& data_list, const Base::ExtraList& extra_list)
{
	enum Columns {CLMN_VIEW_DATE, CLMN_COUNT, CLMN_TITLE, CLMN_GENRES, CLMN_COUNTRIES,
				  CLMN_DIRECTORS, CLMN_ACTORS, CLMN_YEAR, CLMN_RATING};
	initColumns({tr("Регион / Страна / Дата"), tr("К-во"), tr("Название"), tr("Жанр"), tr("Страна"),
				 tr("Режиссёр"), tr("Актёры"), tr("Год"), tr("Оценка")},
				{WIDTH_VIEW_DATE_BIG, WIDTH_COUNT, WIDTH_TITLE, WIDTH_GENRES, WIDTH_COUNTRIES,
				 WIDTH_DIRECTORS, WIDTH_ACTORS, WIDTH_YEAR, WIDTH_RATING});
	initSorting(CLMN_COUNT, Qt::DescendingOrder, true);

	auto synonyms = extra_list.getSynonyms(tr("[Синонимы для стран]"));
	auto movies_by_regions = data_list.moviesByRegions(synonyms, _favorites_only);

	for (const auto& [region, movies_by_countries] : movies_by_regions) {
		auto item_region = new Base::WidgetTreeItem(this, Global::Colors::tree_level_2);
		item_region->setText(CLMN_VIEW_DATE, region);
		std::set<QString> present_countries;
		std::unordered_set<QString> ids;
		uint32_t region_min_year = Global::undefined_value;
		uint32_t region_max_year = Global::undefined_value;

		for (const auto& [country, movies] : movies_by_countries) {
			auto item_country = new Base::WidgetTreeItem(item_region, Global::Colors::tree_level_1);
			item_country->setText(CLMN_VIEW_DATE, country);
			item_country->setNumb(CLMN_COUNT, movies.size());
			item_country->setText(CLMN_YEAR, Helper::yearString(movies));
			present_countries.insert(country);

			for (const auto movie : movies) {
				auto item_movie = new Base::WidgetTreeItem(item_country);
				item_movie->setText(CLMN_VIEW_DATE, movie->viewDateWithoutSeconds());
				item_movie->setText(CLMN_TITLE, movie->title());
				item_movie->setText(CLMN_GENRES, movie->genresToString());
				item_movie->setText(CLMN_COUNTRIES, movie->countriesToString());
				item_movie->setText(CLMN_DIRECTORS, movie->directorsToString());
				item_movie->setText(CLMN_ACTORS, movie->actorsToString());
				item_movie->setText(CLMN_YEAR, movie->yearString());
				item_movie->setRating(CLMN_RATING, movie->rating());
				item_movie->setToolTipEverywhere(movie->summaryString());
				item_movie->setId(movie->id());
				ids.insert(movie->id());
				Helper::checkMinMax(movie->year(), &region_min_year, &region_max_year);
			}
		}

		item_region->setNumb(CLMN_COUNT, ids.size());
		item_region->setText(CLMN_YEAR, Helper::yearString(region_min_year, region_max_year));
		item_region->setToolTipEverywhere(Regions::progress(region, present_countries));
	}
}

void Movies::WidgetDataList::showByYears(const DataList& data_list)
{
	enum Columns {CLMN_VIEW_DATE, CLMN_COUNT, CLMN_TITLE, CLMN_GENRES, CLMN_COUNTRIES,
				  CLMN_DIRECTORS, CLMN_ACTORS, CLMN_YEAR, CLMN_RATING};
	initColumns({tr("Год / Дата"), tr("К-во"), tr("Название"), tr("Жанр"), tr("Страна"),
				 tr("Режиссёр"), tr("Актёры"), tr("Год"), tr("Оценка")},
				{WIDTH_VIEW_DATE_MEDIUM, WIDTH_COUNT, WIDTH_TITLE, WIDTH_GENRES, WIDTH_COUNTRIES,
				 WIDTH_DIRECTORS, WIDTH_ACTORS, WIDTH_YEAR, WIDTH_RATING});
	initSorting(CLMN_VIEW_DATE, Qt::DescendingOrder, true);

	auto movies_by_years = data_list.moviesByYears(1, _favorites_only);

	for (const auto& [year, movies] : movies_by_years) {
		auto item_year = new Base::WidgetTreeItem(this, Global::Colors::tree_level_1);
		item_year->setText(CLMN_VIEW_DATE, year);
		item_year->setNumb(CLMN_COUNT, movies.size());
		item_year->setText(CLMN_YEAR, Helper::yearString(movies));

		for (const auto movie : movies) {
			auto item_movie = new Base::WidgetTreeItem(item_year);
			item_movie->setText(CLMN_VIEW_DATE, movie->viewDateWithoutSeconds());
			item_movie->setText(CLMN_TITLE, movie->title());
			item_movie->setText(CLMN_GENRES, movie->genresToString());
			item_movie->setText(CLMN_COUNTRIES, movie->countriesToString());
			item_movie->setText(CLMN_DIRECTORS, movie->directorsToString());
			item_movie->setText(CLMN_ACTORS, movie->actorsToString());
			item_movie->setText(CLMN_YEAR, movie->yearString());
			item_movie->setRating(CLMN_RATING, movie->rating());
			item_movie->setToolTipEverywhere(movie->summaryString());
			item_movie->setId(movie->id());
		}
	}
}

void Movies::WidgetDataList::showByDecades(const DataList& data_list)
{
	enum Columns {CLMN_VIEW_DATE, CLMN_COUNT, CLMN_TITLE, CLMN_GENRES, CLMN_COUNTRIES,
				  CLMN_DIRECTORS, CLMN_ACTORS, CLMN_YEAR, CLMN_RATING};
	initColumns({tr("Десятилетие / Дата"), tr("К-во"), tr("Название"), tr("Жанр"), tr("Страна"),
				 tr("Режиссёр"), tr("Актёры"), tr("Год"), tr("Оценка")},
				{WIDTH_VIEW_DATE_MEDIUM, WIDTH_COUNT, WIDTH_TITLE, WIDTH_GENRES, WIDTH_COUNTRIES,
				 WIDTH_DIRECTORS, WIDTH_ACTORS, WIDTH_YEAR, WIDTH_RATING});
	initSorting(CLMN_VIEW_DATE, Qt::DescendingOrder, true);

	auto movies_by_years = data_list.moviesByYears(10, _favorites_only);

	for (const auto& [decade, movies] : movies_by_years) {
		auto item_decade = new Base::WidgetTreeItem(this, Global::Colors::tree_level_1);
		item_decade->setText(CLMN_VIEW_DATE, decade);
		item_decade->setNumb(CLMN_COUNT, movies.size());
		item_decade->setText(CLMN_YEAR, Helper::yearString(movies));

		for (const auto movie : movies) {
			auto item_movie = new Base::WidgetTreeItem(item_decade);
			item_movie->setText(CLMN_VIEW_DATE, movie->viewDateWithoutSeconds());
			item_movie->setText(CLMN_TITLE, movie->title());
			item_movie->setText(CLMN_GENRES, movie->genresToString());
			item_movie->setText(CLMN_COUNTRIES, movie->countriesToString());
			item_movie->setText(CLMN_DIRECTORS, movie->directorsToString());
			item_movie->setText(CLMN_ACTORS, movie->actorsToString());
			item_movie->setText(CLMN_YEAR, movie->yearString());
			item_movie->setRating(CLMN_RATING, movie->rating());
			item_movie->setToolTipEverywhere(movie->summaryString());
			item_movie->setId(movie->id());
		}
	}
}

void Movies::WidgetDataList::showByDirectors(const DataList& data_list)
{
	enum Columns {CLMN_VIEW_DATE, CLMN_COUNT, CLMN_TITLE, CLMN_GENRES, CLMN_COUNTRIES,
				  CLMN_DIRECTORS, CLMN_ACTORS, CLMN_YEAR, CLMN_RATING};
	initColumns({tr("Режиссёр / Дата"), tr("К-во"), tr("Название"), tr("Жанр"), tr("Страна"),
				 tr("Режиссёр"), tr("Актёры"), tr("Год"), tr("Оценка")},
				{WIDTH_VIEW_DATE_BIG, WIDTH_COUNT, WIDTH_TITLE, WIDTH_GENRES, WIDTH_COUNTRIES,
				 WIDTH_DIRECTORS, WIDTH_ACTORS, WIDTH_YEAR, WIDTH_RATING});
	initSorting(CLMN_COUNT, Qt::DescendingOrder, true);

	auto movies_by_directors = data_list.moviesByDirectors(_favorites_only);

	for (const auto& [director, movies] : movies_by_directors) {
		if (!_favorites_only && (movies.size() < 5)) { continue; }
		auto item_director = new Base::WidgetTreeItem(this, Global::Colors::tree_level_1);
		item_director->setText(CLMN_VIEW_DATE, director);
		item_director->setNumb(CLMN_COUNT, movies.size());
		item_director->setText(CLMN_YEAR, Helper::yearString(movies));

		for (const auto movie : movies) {
			auto item_movie = new Base::WidgetTreeItem(item_director);
			item_movie->setText(CLMN_VIEW_DATE, movie->viewDateWithoutSeconds());
			item_movie->setText(CLMN_TITLE, movie->title());
			item_movie->setText(CLMN_GENRES, movie->genresToString());
			item_movie->setText(CLMN_COUNTRIES, movie->countriesToString());
			item_movie->setText(CLMN_DIRECTORS, movie->directorsToString());
			item_movie->setText(CLMN_ACTORS, movie->actorsToString());
			item_movie->setText(CLMN_YEAR, movie->yearString());
			item_movie->setRating(CLMN_RATING, movie->rating());
			item_movie->setToolTipEverywhere(movie->summaryString());
			item_movie->setId(movie->id());
		}
	}
}

void Movies::WidgetDataList::showByWriters(const DataList& data_list)
{
	enum Columns {CLMN_VIEW_DATE, CLMN_COUNT, CLMN_TITLE, CLMN_GENRES, CLMN_COUNTRIES,
				  CLMN_DIRECTORS, CLMN_ACTORS, CLMN_YEAR, CLMN_RATING};
	initColumns({tr("Сценарист / Дата"), tr("К-во"), tr("Название"), tr("Жанр"), tr("Страна"),
				 tr("Режиссёр"), tr("Актёры"), tr("Год"), tr("Оценка")},
				{WIDTH_VIEW_DATE_BIG, WIDTH_COUNT, WIDTH_TITLE, WIDTH_GENRES, WIDTH_COUNTRIES,
				 WIDTH_DIRECTORS, WIDTH_ACTORS, WIDTH_YEAR, WIDTH_RATING});
	initSorting(CLMN_COUNT, Qt::DescendingOrder, true);

	auto movies_by_writers = data_list.moviesByWriters(_favorites_only);

	for (const auto& [writer, movies] : movies_by_writers) {
		if (!_favorites_only && (movies.size() < 5)) { continue; }
		auto item_writer = new Base::WidgetTreeItem(this, Global::Colors::tree_level_1);
		item_writer->setText(CLMN_VIEW_DATE, writer);
		item_writer->setNumb(CLMN_COUNT, movies.size());
		item_writer->setText(CLMN_YEAR, Helper::yearString(movies));

		for (const auto movie : movies) {
			auto item_movie = new Base::WidgetTreeItem(item_writer);
			item_movie->setText(CLMN_VIEW_DATE, movie->viewDateWithoutSeconds());
			item_movie->setText(CLMN_TITLE, movie->title());
			item_movie->setText(CLMN_GENRES, movie->genresToString());
			item_movie->setText(CLMN_COUNTRIES, movie->countriesToString());
			item_movie->setText(CLMN_DIRECTORS, movie->directorsToString());
			item_movie->setText(CLMN_ACTORS, movie->actorsToString());
			item_movie->setText(CLMN_YEAR, movie->yearString());
			item_movie->setRating(CLMN_RATING, movie->rating());
			item_movie->setToolTipEverywhere(movie->summaryString());
			item_movie->setId(movie->id());
		}
	}
}

void Movies::WidgetDataList::showByActors(const DataList& data_list)
{
	enum Columns {CLMN_VIEW_DATE, CLMN_COUNT, CLMN_TITLE, CLMN_GENRES, CLMN_COUNTRIES,
				  CLMN_DIRECTORS, CLMN_ACTORS, CLMN_YEAR, CLMN_RATING};
	initColumns({tr("Актёр / Дата"), tr("К-во"), tr("Название"), tr("Жанр"), tr("Страна"),
				 tr("Режиссёр"), tr("Актёры"), tr("Год"), tr("Оценка")},
				{WIDTH_VIEW_DATE_BIG, WIDTH_COUNT, WIDTH_TITLE, WIDTH_GENRES, WIDTH_COUNTRIES,
				 WIDTH_DIRECTORS, WIDTH_ACTORS, WIDTH_YEAR, WIDTH_RATING});
	initSorting(CLMN_COUNT, Qt::DescendingOrder, true);

	auto movies_by_actors = data_list.moviesByActors(_favorites_only);

	for (const auto& [actor, movies] : movies_by_actors) {
		if (!_favorites_only && (movies.size() < 5)) { continue; }
		auto item_actor = new Base::WidgetTreeItem(this, Global::Colors::tree_level_1);
		item_actor->setText(CLMN_VIEW_DATE, actor);
		item_actor->setNumb(CLMN_COUNT, movies.size());
		item_actor->setText(CLMN_YEAR, Helper::yearString(movies));

		for (const auto movie : movies) {
			auto item_movie = new Base::WidgetTreeItem(item_actor);
			item_movie->setText(CLMN_VIEW_DATE, movie->viewDateWithoutSeconds());
			item_movie->setText(CLMN_TITLE, movie->title());
			item_movie->setText(CLMN_GENRES, movie->genresToString());
			item_movie->setText(CLMN_COUNTRIES, movie->countriesToString());
			item_movie->setText(CLMN_DIRECTORS, movie->directorsToString());
			item_movie->setText(CLMN_ACTORS, movie->actorsToString());
			item_movie->setText(CLMN_YEAR, movie->yearString());
			item_movie->setRating(CLMN_RATING, movie->rating());
			item_movie->setToolTipEverywhere(movie->summaryString());
			item_movie->setId(movie->id());
		}
	}
}

void Movies::WidgetDataList::showByRatings(const DataList& data_list)
{
	enum Columns {CLMN_VIEW_DATE, CLMN_COUNT, CLMN_TITLE, CLMN_GENRES, CLMN_COUNTRIES,
				  CLMN_DIRECTORS, CLMN_ACTORS, CLMN_YEAR};
	initColumns({tr("Оценка / Дата"), tr("К-во"), tr("Название"), tr("Жанр"), tr("Страна"),
				 tr("Режиссёр"), tr("Актёры"), tr("Год")},
				{WIDTH_VIEW_DATE_MEDIUM, WIDTH_COUNT, WIDTH_TITLE, WIDTH_GENRES, WIDTH_COUNTRIES,
				 WIDTH_DIRECTORS, WIDTH_ACTORS, WIDTH_YEAR});
	initSorting(CLMN_VIEW_DATE, Qt::AscendingOrder, true);

	auto movies_by_ratings = data_list.moviesByRatings(_favorites_only);

	for (const auto& [rating, movies] : movies_by_ratings) {
		auto item_rating = new Base::WidgetTreeItem(this, Helper::ratingColor(rating));
		item_rating->setNumb(CLMN_VIEW_DATE, rating);
		item_rating->setNumb(CLMN_COUNT, movies.size());
		item_rating->setText(CLMN_YEAR, Helper::yearString(movies));

		for (const auto movie : movies) {
			auto item_movie = new Base::WidgetTreeItem(item_rating);
			item_movie->setText(CLMN_VIEW_DATE, movie->viewDateWithoutSeconds());
			item_movie->setText(CLMN_TITLE, movie->title());
			item_movie->setText(CLMN_GENRES, movie->genresToString());
			item_movie->setText(CLMN_COUNTRIES, movie->countriesToString());
			item_movie->setText(CLMN_DIRECTORS, movie->directorsToString());
			item_movie->setText(CLMN_ACTORS, movie->actorsToString());
			item_movie->setText(CLMN_YEAR, movie->yearString());
			item_movie->setToolTipEverywhere(movie->summaryString());
			item_movie->setId(movie->id());
		}
	}
}
