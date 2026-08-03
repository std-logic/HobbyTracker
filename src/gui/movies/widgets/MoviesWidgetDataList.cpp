#include "MoviesWidgetDataList.h"
#include "../common/MoviesCommon.h"
#include "../data/MoviesDataList.h"

#include <gui/base/widgets/BaseWidgetTreeItem.h>

Movies::WidgetDataList::WidgetDataList(QWidget* parent)
	: Base::WidgetTree{parent}
{
}

void Movies::WidgetDataList::update(const DataList& data_list)
{
	clear();
	setRootIsDecorated(static_cast<DataListViewModes>(_view_mode) != DataListViewModes::Simple);
	switch (static_cast<DataListViewModes>(_view_mode)) {
		case DataListViewModes::Simple:			showSimple(data_list);			break;
		case DataListViewModes::ByGenres:		showByGenres(data_list);		break;
		case DataListViewModes::ByCountries:	showByCountries(data_list);		break;
		case DataListViewModes::ByYears:		showByYears(data_list);			break;
		case DataListViewModes::ByDecades:		showByDecades(data_list);		break;
		case DataListViewModes::ByDirectors:	showByDirectors(data_list);		break;
		case DataListViewModes::ByWriters:		showByWriters(data_list);		break;
		case DataListViewModes::ByActors:		showByActors(data_list);		break;
		case DataListViewModes::ByRatings:		showByRatings(data_list);		break;
		default: return;
	}
}

void Movies::WidgetDataList::showSimple(const DataList& data_list)
{
	enum Columns {CLMN_VIEW_DATE, CLMN_TITLE, CLMN_GENRES, CLMN_COUNTRIES,
				  CLMN_DIRECTORS, CLMN_ACTORS, CLMN_YEAR, CLMN_RATING};
	initColumns({tr("Дата"), tr("Название"), tr("Жанр"), tr("Страна"),
				 tr("Режиссёр"), tr("Актёры"), tr("Год"), tr("Оценка")},
				{WIDTH_VIEW_DATE, WIDTH_TITLE, WIDTH_GENRES, WIDTH_COUNTRIES,
				 WIDTH_DIRECTORS, WIDTH_ACTORS, WIDTH_YEAR, WIDTH_RATING});
	initSorting(CLMN_VIEW_DATE, Qt::DescendingOrder);

	for (const auto& movie : data_list) {
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

void Movies::WidgetDataList::showByGenres(const DataList& data_list)
{
	// enum Columns {CLMN_TITLE, CLMN_COUNT, CLMN_YEAR, CLMN_RATING};
	// initColumns({tr("Жанр / Название"), tr("К-во"), tr("Год"), tr("Оценка")},
	// 			{WIDTH_TITLE, WIDTH_COUNT, WIDTH_YEAR, WIDTH_RATING});
	// initSorting(CLMN_TITLE);

	// auto books_by_genres = data_list.booksByGenres();

	// for (const auto& [genre, books] : books_by_genres) {
	// 	auto item_genre = new Base::WidgetTreeItem(this, Global::Colors::tree_level_1);
	// 	item_genre->setText(CLMN_TITLE, genre);
	// 	item_genre->setNumb(CLMN_COUNT, books.size());
	// 	item_genre->setText(CLMN_YEAR, Helper::yearString(books));

	// 	for (const auto book : books) {
	// 		auto item_book = new Base::WidgetTreeItem(item_genre);
	// 		item_book->setText(CLMN_TITLE, book->autorAndTitle());
	// 		item_book->setToolTip(CLMN_TITLE, book->summaryString());
	// 		item_book->setText(CLMN_YEAR, book->yearString());
	// 		item_book->setRating(CLMN_RATING, book->rating());
	// 		item_book->setId(book->id());
	// 	}
	// }
}

void Movies::WidgetDataList::showByCountries(const DataList& data_list)
{
	// enum Columns {CLMN_TITLE, CLMN_COUNT, CLMN_GENRE, CLMN_YEAR, CLMN_RATING};
	// initColumns({tr("Автор / Название"), tr("К-во"), tr("Жанр"), tr("Год"), tr("Оценка")},
	// 			{WIDTH_TITLE, WIDTH_COUNT, WIDTH_GENRE, WIDTH_YEAR, WIDTH_RATING});
	// initSorting(CLMN_TITLE);

	// auto books_by_authors = data_list.booksByAuthors();

	// for (const auto& [author, books] : books_by_authors) {
	// 	auto item_author = new Base::WidgetTreeItem(this, Global::Colors::tree_level_1);
	// 	item_author->setText(CLMN_TITLE, author);
	// 	item_author->setNumb(CLMN_COUNT, books.size());
	// 	item_author->setText(CLMN_YEAR, Helper::yearString(books));

	// 	for (const auto book : books) {
	// 		auto item_book = new Base::WidgetTreeItem(item_author);
	// 		item_book->setText(CLMN_TITLE, book->title());
	// 		item_book->setToolTip(CLMN_TITLE, book->summaryString());
	// 		item_book->setText(CLMN_GENRE, book->genre());
	// 		item_book->setText(CLMN_YEAR, book->yearString());
	// 		item_book->setRating(CLMN_RATING, book->rating());
	// 		item_book->setId(book->id());
	// 	}
	// }
}

void Movies::WidgetDataList::showByYears(const DataList& data_list)
{
	// enum Columns {CLMN_TITLE, CLMN_COUNT, CLMN_GENRE, CLMN_YEAR, CLMN_RATING};
	// initColumns({tr("Столетие / Название"), tr("К-во"), tr("Жанр"), tr("Год"), tr("Оценка")},
	// 			{WIDTH_TITLE, WIDTH_COUNT, WIDTH_GENRE, WIDTH_YEAR, WIDTH_RATING});
	// initSorting(CLMN_TITLE);

	// auto books_by_years = data_list.booksByYears(100);

	// for (const auto& [century, books] : books_by_years) {
	// 	auto item_century = new Base::WidgetTreeItem(this, Global::Colors::tree_level_1);
	// 	item_century->setText(CLMN_TITLE, century);
	// 	item_century->setNumb(CLMN_COUNT, books.size());
	// 	item_century->setText(CLMN_YEAR, Helper::yearString(books));

	// 	for (const auto book : books) {
	// 		auto item_book = new Base::WidgetTreeItem(item_century);
	// 		item_book->setText(CLMN_TITLE, book->autorAndTitle());
	// 		item_book->setToolTip(CLMN_TITLE, book->summaryString());
	// 		item_book->setText(CLMN_GENRE, book->genre());
	// 		item_book->setText(CLMN_YEAR, book->yearString());
	// 		item_book->setRating(CLMN_RATING, book->rating());
	// 		item_book->setId(book->id());
	// 	}
	// }
}

void Movies::WidgetDataList::showByDecades(const DataList& data_list)
{
	// enum Columns {CLMN_TITLE, CLMN_COUNT, CLMN_GENRE, CLMN_YEAR, CLMN_RATING};
	// initColumns({tr("Десятилетие / Название"), tr("К-во"), tr("Жанр"), tr("Год"), tr("Оценка")},
	// 			{WIDTH_TITLE, WIDTH_COUNT, WIDTH_GENRE, WIDTH_YEAR, WIDTH_RATING});
	// initSorting(CLMN_TITLE);

	// auto books_by_years = data_list.booksByYears(10);

	// for (const auto& [decade, books] : books_by_years) {
	// 	auto item_decade = new Base::WidgetTreeItem(this, Global::Colors::tree_level_1);
	// 	item_decade->setText(CLMN_TITLE, decade);
	// 	item_decade->setNumb(CLMN_COUNT, books.size());
	// 	item_decade->setText(CLMN_YEAR, Helper::yearString(books));

	// 	for (const auto book : books) {
	// 		auto item_book = new Base::WidgetTreeItem(item_decade);
	// 		item_book->setText(CLMN_TITLE, book->autorAndTitle());
	// 		item_book->setToolTip(CLMN_TITLE, book->summaryString());
	// 		item_book->setText(CLMN_GENRE, book->genre());
	// 		item_book->setText(CLMN_YEAR, book->yearString());
	// 		item_book->setRating(CLMN_RATING, book->rating());
	// 		item_book->setId(book->id());
	// 	}
	// }
}

void Movies::WidgetDataList::showByDirectors(const DataList& data_list)
{
	// enum Columns {CLMN_TITLE, CLMN_COUNT, CLMN_GENRE, CLMN_YEAR};
	// initColumns({tr("Оценка / Название"), tr("К-во"), tr("Жанр"), tr("Год")},
	// 			{WIDTH_TITLE, WIDTH_COUNT, WIDTH_GENRE, WIDTH_YEAR});
	// initSorting(CLMN_TITLE);

	// auto books_by_ratings = data_list.booksByRatings();

	// for (const auto& [rating, books] : books_by_ratings) {
	// 	auto item_rating = new Base::WidgetTreeItem(this, Helper::ratingColor(rating));
	// 	item_rating->setNumb(CLMN_TITLE, rating);
	// 	item_rating->setNumb(CLMN_COUNT, books.size());
	// 	item_rating->setText(CLMN_YEAR, Helper::yearString(books));

	// 	for (const auto book : books) {
	// 		auto item_book = new Base::WidgetTreeItem(item_rating);
	// 		item_book->setText(CLMN_TITLE, book->autorAndTitle());
	// 		item_book->setToolTip(CLMN_TITLE, book->summaryString());
	// 		item_book->setText(CLMN_GENRE, book->genre());
	// 		item_book->setText(CLMN_YEAR, book->yearString());
	// 		item_book->setId(book->id());
	// 	}
	// }
}

void Movies::WidgetDataList::showByWriters(const DataList& data_list)
{
	// enum Columns {CLMN_TITLE, CLMN_COUNT, CLMN_GENRE, CLMN_YEAR};
	// initColumns({tr("Оценка / Название"), tr("К-во"), tr("Жанр"), tr("Год")},
	// 			{WIDTH_TITLE, WIDTH_COUNT, WIDTH_GENRE, WIDTH_YEAR});
	// initSorting(CLMN_TITLE);

	// auto books_by_ratings = data_list.booksByRatings();

	// for (const auto& [rating, books] : books_by_ratings) {
	// 	auto item_rating = new Base::WidgetTreeItem(this, Helper::ratingColor(rating));
	// 	item_rating->setNumb(CLMN_TITLE, rating);
	// 	item_rating->setNumb(CLMN_COUNT, books.size());
	// 	item_rating->setText(CLMN_YEAR, Helper::yearString(books));

	// 	for (const auto book : books) {
	// 		auto item_book = new Base::WidgetTreeItem(item_rating);
	// 		item_book->setText(CLMN_TITLE, book->autorAndTitle());
	// 		item_book->setToolTip(CLMN_TITLE, book->summaryString());
	// 		item_book->setText(CLMN_GENRE, book->genre());
	// 		item_book->setText(CLMN_YEAR, book->yearString());
	// 		item_book->setId(book->id());
	// 	}
	// }
}

void Movies::WidgetDataList::showByActors(const DataList& data_list)
{
	// enum Columns {CLMN_TITLE, CLMN_COUNT, CLMN_GENRE, CLMN_YEAR};
	// initColumns({tr("Оценка / Название"), tr("К-во"), tr("Жанр"), tr("Год")},
	// 			{WIDTH_TITLE, WIDTH_COUNT, WIDTH_GENRE, WIDTH_YEAR});
	// initSorting(CLMN_TITLE);

	// auto books_by_ratings = data_list.booksByRatings();

	// for (const auto& [rating, books] : books_by_ratings) {
	// 	auto item_rating = new Base::WidgetTreeItem(this, Helper::ratingColor(rating));
	// 	item_rating->setNumb(CLMN_TITLE, rating);
	// 	item_rating->setNumb(CLMN_COUNT, books.size());
	// 	item_rating->setText(CLMN_YEAR, Helper::yearString(books));

	// 	for (const auto book : books) {
	// 		auto item_book = new Base::WidgetTreeItem(item_rating);
	// 		item_book->setText(CLMN_TITLE, book->autorAndTitle());
	// 		item_book->setToolTip(CLMN_TITLE, book->summaryString());
	// 		item_book->setText(CLMN_GENRE, book->genre());
	// 		item_book->setText(CLMN_YEAR, book->yearString());
	// 		item_book->setId(book->id());
	// 	}
	// }
}

void Movies::WidgetDataList::showByRatings(const DataList& data_list)
{
	// enum Columns {CLMN_TITLE, CLMN_COUNT, CLMN_GENRE, CLMN_YEAR};
	// initColumns({tr("Оценка / Название"), tr("К-во"), tr("Жанр"), tr("Год")},
	// 			{WIDTH_TITLE, WIDTH_COUNT, WIDTH_GENRE, WIDTH_YEAR});
	// initSorting(CLMN_TITLE);

	// auto books_by_ratings = data_list.booksByRatings();

	// for (const auto& [rating, books] : books_by_ratings) {
	// 	auto item_rating = new Base::WidgetTreeItem(this, Helper::ratingColor(rating));
	// 	item_rating->setNumb(CLMN_TITLE, rating);
	// 	item_rating->setNumb(CLMN_COUNT, books.size());
	// 	item_rating->setText(CLMN_YEAR, Helper::yearString(books));

	// 	for (const auto book : books) {
	// 		auto item_book = new Base::WidgetTreeItem(item_rating);
	// 		item_book->setText(CLMN_TITLE, book->autorAndTitle());
	// 		item_book->setToolTip(CLMN_TITLE, book->summaryString());
	// 		item_book->setText(CLMN_GENRE, book->genre());
	// 		item_book->setText(CLMN_YEAR, book->yearString());
	// 		item_book->setId(book->id());
	// 	}
	// }
}
