#include "MusicWidgetDataList.h"
#include "../common/MusicCommon.h"
#include "../data/MusicDataList.h"

#include <gui/base/widgets/BaseWidgetTreeItem.h>

Music::WidgetDataList::WidgetDataList(QWidget* parent)
	: Base::WidgetTree{parent}
{
}

void Music::WidgetDataList::update(const DataList& data_list)
{
	clear();
	setRootIsDecorated(static_cast<DataListViewModes>(_view_mode) != DataListViewModes::Simple);
	switch (static_cast<DataListViewModes>(_view_mode)) {
		case DataListViewModes::Simple:			showSimple(data_list);			break;
		case DataListViewModes::ByGenres:		showByGenres(data_list);		break;
		case DataListViewModes::ByCountries:	showByCountries(data_list);		break;
		case DataListViewModes::ByDecades:		showByDecades(data_list);		break;
		case DataListViewModes::ByStates:		showByStates(data_list);		break;
		default: return;
	}
}

void Music::WidgetDataList::showSimple(const DataList& data_list)
{
	enum Columns {CLMN_TITLE, CLMN_GENRE, CLMN_COUNTRY, CLMN_YEAR, CLMN_STATE};
	initColumns({tr("Название"), tr("Жанр"), tr("Страна основания"),
				 tr("Год основания"), tr("Статус")},
				{WIDTH_TITLE, WIDTH_GENRE, WIDTH_COUNTRY, WIDTH_YEAR, WIDTH_STATE});
	initSorting(CLMN_TITLE);

	for (const auto& artist : data_list) {
		auto item_artist = new Base::WidgetTreeItem(this);
		item_artist->setText(CLMN_TITLE, artist.title());
		item_artist->setText(CLMN_GENRE, artist.genre());
		item_artist->setText(CLMN_COUNTRY, artist.country());
		item_artist->setText(CLMN_YEAR, artist.yearString());
		item_artist->setText(CLMN_STATE, artist.stateString());
		item_artist->setBackground(CLMN_STATE, artist.stateColor());
		item_artist->setId(artist.id());
	}
}

void Music::WidgetDataList::showByGenres(const DataList& data_list)
{
	enum Columns {CLMN_TITLE, CLMN_COUNT, CLMN_COUNTRY, CLMN_YEAR, CLMN_STATE};
	initColumns({tr("Жанр / Название"), tr("К-во"), tr("Страна основания"),
				 tr("Год основания"), tr("Статус")},
				{WIDTH_TITLE, WIDTH_COUNT, WIDTH_COUNTRY, WIDTH_YEAR, WIDTH_STATE});
	initSorting(CLMN_TITLE);

	auto artists_by_genres = data_list.artistsByGenres();

	for (const auto& [genre, artists] : artists_by_genres) {
		auto item_genre = new Base::WidgetTreeItem(this, Global::Colors::tree_level_1);
		item_genre->setText(CLMN_TITLE, genre);
		item_genre->setNumb(CLMN_COUNT, artists.size());
		item_genre->setText(CLMN_YEAR, Helper::yearString(artists));

		for (const auto artist : artists) {
			auto item_artist = new Base::WidgetTreeItem(item_genre);
			item_artist->setText(CLMN_TITLE, artist->title());
			item_artist->setText(CLMN_COUNTRY, artist->country());
			item_artist->setText(CLMN_YEAR, artist->yearString());
			item_artist->setText(CLMN_STATE, artist->stateString());
			item_artist->setBackground(CLMN_STATE, artist->stateColor());
			item_artist->setId(artist->id());
		}
	}
}

void Music::WidgetDataList::showByCountries(const DataList& data_list)
{
	enum Columns {CLMN_TITLE, CLMN_COUNT, CLMN_GENRE, CLMN_YEAR, CLMN_STATE};
	initColumns({tr("Страна основания / Название"), tr("К-во"), tr("Жанр"),
				 tr("Год основания"), tr("Статус")},
				{WIDTH_TITLE, WIDTH_COUNT, WIDTH_GENRE, WIDTH_YEAR, WIDTH_STATE});
	initSorting(CLMN_TITLE);

	auto artists_by_countries = data_list.artistsByCountries();

	for (const auto& [country, artists] : artists_by_countries) {
		auto item_country = new Base::WidgetTreeItem(this, Global::Colors::tree_level_1);
		item_country->setText(CLMN_TITLE, country);
		item_country->setNumb(CLMN_COUNT, artists.size());
		item_country->setText(CLMN_YEAR, Helper::yearString(artists));

		for (const auto artist : artists) {
			auto item_artist = new Base::WidgetTreeItem(item_country);
			item_artist->setText(CLMN_TITLE, artist->title());
			item_artist->setText(CLMN_GENRE, artist->genre());
			item_artist->setText(CLMN_YEAR, artist->yearString());
			item_artist->setText(CLMN_STATE, artist->stateString());
			item_artist->setBackground(CLMN_STATE, artist->stateColor());
			item_artist->setId(artist->id());
		}
	}
}

void Music::WidgetDataList::showByDecades(const DataList& data_list)
{
	enum Columns {CLMN_TITLE, CLMN_COUNT, CLMN_GENRE, CLMN_COUNTRY, CLMN_YEAR, CLMN_STATE};
	initColumns({tr("Десятилетие основания / Название"), tr("К-во"), tr("Жанр"),
				 tr("Страна основания"), tr("Год основания"), tr("Статус")},
				{WIDTH_TITLE, WIDTH_COUNT, WIDTH_GENRE, WIDTH_COUNTRY, WIDTH_YEAR, WIDTH_STATE});
	initSorting(CLMN_TITLE);

	auto artists_by_years = data_list.artistsByYears(10);

	for (const auto& [decade, artists] : artists_by_years) {
		auto item_decade = new Base::WidgetTreeItem(this, Global::Colors::tree_level_1);
		item_decade->setText(CLMN_TITLE, decade);
		item_decade->setNumb(CLMN_COUNT, artists.size());
		item_decade->setText(CLMN_YEAR, Helper::yearString(artists));

		for (const auto artist : artists) {
			auto item_artist = new Base::WidgetTreeItem(item_decade);
			item_artist->setText(CLMN_TITLE, artist->title());
			item_artist->setText(CLMN_GENRE, artist->genre());
			item_artist->setText(CLMN_COUNTRY, artist->country());
			item_artist->setText(CLMN_YEAR, artist->yearString());
			item_artist->setText(CLMN_STATE, artist->stateString());
			item_artist->setBackground(CLMN_STATE, artist->stateColor());
			item_artist->setId(artist->id());
		}
	}
}

void Music::WidgetDataList::showByStates(const DataList& data_list)
{
	enum Columns {CLMN_TITLE, CLMN_COUNT, CLMN_GENRE, CLMN_COUNTRY, CLMN_YEAR};
	initColumns({tr("Статус / Название"), tr("К-во"), tr("Жанр"),
				 tr("Страна основания"), tr("Год основания")},
				{WIDTH_TITLE, WIDTH_COUNT, WIDTH_GENRE, WIDTH_COUNTRY, WIDTH_YEAR});
	initSorting(CLMN_TITLE);

	auto artists_by_states = data_list.artistsByStates();

	for (const auto& [state, artists] : artists_by_states) {
		auto item_state = new Base::WidgetTreeItem(this, Data::stateColor(static_cast<States>(state)));
		item_state->setText(CLMN_TITLE, Data::stateString(static_cast<States>(state)));
		item_state->setNumb(CLMN_COUNT, artists.size());
		item_state->setText(CLMN_YEAR, Helper::yearString(artists));

		for (const auto artist : artists) {
			auto item_artist = new Base::WidgetTreeItem(item_state);
			item_artist->setText(CLMN_TITLE, artist->title());
			item_artist->setText(CLMN_GENRE, artist->genre());
			item_artist->setText(CLMN_COUNTRY, artist->country());
			item_artist->setText(CLMN_YEAR, artist->yearString());
			item_artist->setId(artist->id());
		}
	}
}
