#include "BooksWidgetList.h"
#include "../common/BooksCommon.h"
#include "../data/BooksDataList.h"

#include <gui/base/widgets/BaseWidgetTreeItem.h>

Books::WidgetList::WidgetList(QWidget* parent)
	: Base::WidgetTree{parent}
{
}

void Books::WidgetList::update(const DataList& list)
{
	clear();
	switch (static_cast<ListViewModes>(_view_mode)) {
		case ListViewModes::ByAuthors:		showByAuthors(list);		break;
		case ListViewModes::ByGenres:		showByGenres(list);			break;
		case ListViewModes::ByDecades:		showByDecades(list);		break;
		case ListViewModes::ByCenturies:	showByCenturies(list);		break;
		case ListViewModes::ByRatings:		showByRatings(list);		break;
		case ListViewModes::Simple:			showSimple(list);			break;
		default: return;
	}
}

void Books::WidgetList::showByAuthors(const DataList& list)
{
	enum Columns {CLMN_TITLE, CLMN_COUNT, CLMN_GENRE, CLMN_YEAR, CLMN_RATING};
	initColumns({tr("Автор / Название"), tr("К-во"), tr("Жанр"), tr("Год"), tr("Оценка")},
				{WIDTH_TITLE, WIDTH_COUNT, WIDTH_GENRE, WIDTH_YEAR, WIDTH_RATING});
	initSorting(CLMN_TITLE);

	auto list_by_authors = list.listByAuthors();

	for (const auto& [author, books] : list_by_authors) {
		auto item_author = new Base::WidgetTreeItem(this, Global::Colors::tree_level_1);
		item_author->setText(CLMN_TITLE, author);
		item_author->setNumb(CLMN_COUNT, books.size());
		item_author->setText(CLMN_YEAR, Helper::yearString(DataList::sublistMinMaxYears(books)));

		for (const auto book : books) {
			auto item_book = new Base::WidgetTreeItem(item_author);
			item_book->setText(CLMN_TITLE, book->title());
			item_book->setText(CLMN_GENRE, book->genre());
			item_book->setText(CLMN_YEAR, book->yearString());
			item_book->setRating(CLMN_RATING, book->rating());
		}
	}
}

void Books::WidgetList::showByGenres(const DataList& list)
{
	enum Columns {CLMN_TITLE, CLMN_COUNT, CLMN_YEAR, CLMN_RATING};
	initColumns({tr("Жанр / Название"), tr("К-во"), tr("Год"), tr("Оценка")},
				{WIDTH_TITLE, WIDTH_COUNT, WIDTH_YEAR, WIDTH_RATING});
	initSorting(CLMN_TITLE);

	auto list_by_genres = list.listByGenres();

	for (const auto& [genre, books] : list_by_genres) {
		auto item_genre = new Base::WidgetTreeItem(this, Global::Colors::tree_level_1);
		item_genre->setText(CLMN_TITLE, genre);
		item_genre->setNumb(CLMN_COUNT, books.size());
		item_genre->setText(CLMN_YEAR, Helper::yearString(DataList::sublistMinMaxYears(books)));

		for (const auto book : books) {
			auto item_book = new Base::WidgetTreeItem(item_genre);
			item_book->setText(CLMN_TITLE, book->autorAndTitle());
			item_book->setText(CLMN_YEAR, book->yearString());
			item_book->setRating(CLMN_RATING, book->rating());
		}
	}
}

void Books::WidgetList::showByDecades(const DataList& list)
{
	enum Columns {CLMN_TITLE, CLMN_COUNT, CLMN_GENRE, CLMN_YEAR, CLMN_RATING};
	initColumns({tr("Десятилетие / Название"), tr("К-во"), tr("Жанр"), tr("Год"), tr("Оценка")},
				{WIDTH_TITLE, WIDTH_COUNT, WIDTH_GENRE, WIDTH_YEAR, WIDTH_RATING});
	initSorting(CLMN_TITLE);

	auto list_by_years = list.listByYears(10);

	for (const auto& [decade, books] : list_by_years) {
		auto item_decade = new Base::WidgetTreeItem(this, Global::Colors::tree_level_1);
		item_decade->setText(CLMN_TITLE, decade);
		item_decade->setNumb(CLMN_COUNT, books.size());
		item_decade->setText(CLMN_YEAR, Helper::yearString(DataList::sublistMinMaxYears(books)));

		for (const auto book : books) {
			auto item_book = new Base::WidgetTreeItem(item_decade);
			item_book->setText(CLMN_TITLE, book->autorAndTitle());
			item_book->setText(CLMN_GENRE, book->genre());
			item_book->setText(CLMN_YEAR, book->yearString());
			item_book->setRating(CLMN_RATING, book->rating());
		}
	}
}

void Books::WidgetList::showByCenturies(const DataList& list)
{
	enum Columns {CLMN_TITLE, CLMN_COUNT, CLMN_GENRE, CLMN_YEAR, CLMN_RATING};
	initColumns({tr("Столетие / Название"), tr("К-во"), tr("Жанр"), tr("Год"), tr("Оценка")},
				{WIDTH_TITLE, WIDTH_COUNT, WIDTH_GENRE, WIDTH_YEAR, WIDTH_RATING});
	initSorting(CLMN_TITLE);

	auto list_by_years = list.listByYears(100);

	for (const auto& [century, books] : list_by_years) {
		auto item_century = new Base::WidgetTreeItem(this, Global::Colors::tree_level_1);
		item_century->setText(CLMN_TITLE, century);
		item_century->setNumb(CLMN_COUNT, books.size());
		item_century->setText(CLMN_YEAR, Helper::yearString(DataList::sublistMinMaxYears(books)));

		for (const auto book : books) {
			auto item_book = new Base::WidgetTreeItem(item_century);
			item_book->setText(CLMN_TITLE, book->autorAndTitle());
			item_book->setText(CLMN_GENRE, book->genre());
			item_book->setText(CLMN_YEAR, book->yearString());
			item_book->setRating(CLMN_RATING, book->rating());
		}
	}
}

void Books::WidgetList::showByRatings(const DataList& list)
{
	enum Columns {CLMN_TITLE, CLMN_COUNT, CLMN_GENRE, CLMN_YEAR};
	initColumns({tr("Оценка / Название"), tr("К-во"), tr("Жанр"), tr("Год")},
				{WIDTH_TITLE, WIDTH_COUNT, WIDTH_GENRE, WIDTH_YEAR});
	initSorting(CLMN_TITLE);

	auto list_by_ratings = list.listByRatings();

	for (const auto& [rating, books] : list_by_ratings) {
		auto item_rating = new Base::WidgetTreeItem(this, Helper::ratingColor(rating));
		item_rating->setNumb(CLMN_TITLE, rating);
		item_rating->setNumb(CLMN_COUNT, books.size());
		item_rating->setText(CLMN_YEAR, Helper::yearString(DataList::sublistMinMaxYears(books)));

		for (const auto book : books) {
			auto item_book = new Base::WidgetTreeItem(item_rating);
			item_book->setText(CLMN_TITLE, book->autorAndTitle());
			item_book->setText(CLMN_GENRE, book->genre());
			item_book->setText(CLMN_YEAR, book->yearString());
		}
	}
}

void Books::WidgetList::showSimple(const DataList& list)
{
	enum Columns {CLMN_TITLE, CLMN_GENRE, CLMN_YEAR, CLMN_RATING};
	initColumns({tr("Название"), tr("Жанр"), tr("Год"), tr("Оценка")},
				{WIDTH_TITLE, WIDTH_GENRE, WIDTH_YEAR, WIDTH_RATING});
	initSorting(CLMN_TITLE);

	for (const auto& book : list) {
		auto item_book = new Base::WidgetTreeItem(this);
		item_book->setText(CLMN_TITLE, book.autorAndTitle());
		item_book->setText(CLMN_GENRE, book.genre());
		item_book->setText(CLMN_YEAR, book.yearString());
		item_book->setRating(CLMN_RATING, book.rating());
	}
}
