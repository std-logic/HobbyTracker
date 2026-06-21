#include "BooksWidgetList.h"
#include "../common/BooksCommon.h"

#include <gui/base/widgets/BaseWidgetTreeItem.h>

Books::WidgetList::WidgetList(QWidget* parent)
	: Base::WidgetTree{parent}
{
}

void Books::WidgetList::showList(const DataList& list)
{
	clear();
	switch (static_cast<ListViewModes>(_view_mode)) {
		case ListViewModes::ByAuthors:		showByAuthors(list);		break;
		case ListViewModes::ByGenres:		showByGenres(list);			break;
		case ListViewModes::ByYears:		showByYears(list);			break;
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
		item_author->setText(CLMN_YEAR, Helper::yearString(Books::DataList::sublistMinMaxYears(books)));

		for (const auto book : books) {
			auto item_book = new Base::WidgetTreeItem(item_author);
			item_book->setText(CLMN_TITLE, book->title());
			item_book->setText(CLMN_GENRE, book->genre());
			item_book->setNumb(CLMN_YEAR, book->year());
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
		item_genre->setText(CLMN_YEAR, Helper::yearString(Books::DataList::sublistMinMaxYears(books)));

		for (const auto book : books) {
			auto item_book = new Base::WidgetTreeItem(item_genre);
			item_book->setText(CLMN_TITLE, book->autorAndTitle());
			item_book->setNumb(CLMN_YEAR, book->year());
			item_book->setRating(CLMN_RATING, book->rating());
		}
	}
}

void Books::WidgetList::showByYears(const DataList& list)
{

}

void Books::WidgetList::showByRatings(const DataList& list)
{

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
		item_book->setNumb(CLMN_YEAR, book.year());
		item_book->setRating(CLMN_RATING, book.rating());
	}
}
