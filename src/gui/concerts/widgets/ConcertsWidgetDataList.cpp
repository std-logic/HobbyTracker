#include "ConcertsWidgetDataList.h"
#include "../common/ConcertsCommon.h"
#include "../data/ConcertsDataList.h"

#include <gui/base/data/BaseExtraList.h>
#include <gui/base/widgets/BaseWidgetTreeItem.h>

Concerts::WidgetDataList::WidgetDataList(QWidget* parent)
	: Base::WidgetTree{parent}
{
}

void Concerts::WidgetDataList::update(const DataList& data_list, const Base::ExtraList& extra_list)
{
	clear();
	setRootIsDecorated(static_cast<DataListViewModes>(_view_mode) != DataListViewModes::Simple);
	switch (static_cast<DataListViewModes>(_view_mode)) {
		case DataListViewModes::ByYears:		showByYears(data_list);					break;
		case DataListViewModes::ByArtists:		showByArtists(data_list, extra_list);	break;
		case DataListViewModes::ByTags:			showByTags(data_list, extra_list);		break;
		case DataListViewModes::ByCountries:	showByCountries(data_list);				break;
		case DataListViewModes::ByCities:		showByCities(data_list);				break;
		case DataListViewModes::ByPlaces:		showByPlaces(data_list, extra_list);	break;
		case DataListViewModes::PlacesTree:		showPlacesTree(data_list, extra_list);	break;
		case DataListViewModes::Simple:			showSimple(data_list);					break;
		default: return;
	}
}

void Concerts::WidgetDataList::setFavoritesState(Qt::CheckState state)
{
	bool favorites_state = (state == Qt::Checked);
	if (_favorites_state == favorites_state) { return; }
	_favorites_state = favorites_state;

	if ((static_cast<DataListViewModes>(_view_mode) == DataListViewModes::ByArtists) ||
		(static_cast<DataListViewModes>(_view_mode) == DataListViewModes::ByPlaces)) {
		emit needUpdate();
	}
}

void Concerts::WidgetDataList::showByYears(const DataList& data_list)
{
	enum Columns {CLMN_DATE, CLMN_COUNT, CLMN_ARTISTS, CLMN_COUNTRY, CLMN_CITY, CLMN_PLACE};
	initColumns({tr("Год / Дата"), tr("К-во"), tr("Группы"), tr("Страна"), tr("Город"), tr("Место")},
				{WIDTH_DATE_SMALL, WIDTH_COUNT, WIDTH_ARTISTS, WIDTH_COUNTRY, WIDTH_CITY, WIDTH_PLACE});
	initSorting(CLMN_DATE);

	auto concerts_by_years = data_list.concertsByYears();

	for (const auto& [year, concerts] : concerts_by_years) {
		auto item_year = new Base::WidgetTreeItem(this, Global::Colors::tree_level_1);
		item_year->setText(CLMN_DATE, year);
		item_year->setNumb(CLMN_COUNT, concerts.size());

		for (const auto concert : concerts) {
			auto item_concert = new Base::WidgetTreeItem(item_year);
			item_concert->setText(CLMN_DATE, concert->date());
			item_concert->setText(CLMN_ARTISTS, concert->artistsAndDescriptionToString(QStringLiteral(" • ")));
			item_concert->setToolTip(CLMN_ARTISTS, concert->summaryString());
			item_concert->setText(CLMN_COUNTRY, concert->country());
			item_concert->setText(CLMN_CITY, concert->city());
			item_concert->setText(CLMN_PLACE, Helper::startWithCapital(concert->place()));
			item_concert->setId(concert->id());
		}
	}
}

void Concerts::WidgetDataList::showByArtists(const DataList& data_list, const Base::ExtraList& extra_list)
{
	enum Columns {CLMN_DATE, CLMN_COUNT, CLMN_ARTISTS, CLMN_COUNTRY, CLMN_CITY, CLMN_PLACE};
	initColumns({tr("Группа / Дата"), tr("К-во"), tr("Группы"), tr("Страна"), tr("Город"), tr("Место")},
				{WIDTH_DATE_MEDIUM, WIDTH_COUNT, WIDTH_ARTISTS, WIDTH_COUNTRY, WIDTH_CITY, WIDTH_PLACE});
	initSorting(CLMN_DATE);

	auto favorites = _favorites_state ?
			DataList::getFavorites(tr("[Избранные группы]"), extra_list) :
			DataList::Favorites();
	auto synonyms = DataList::getSynonyms(tr("[Синонимы для групп]"), extra_list);
	auto concerts_by_artists = data_list.concertsByArtists(synonyms);

	for (const auto& [artist, concerts] : concerts_by_artists) {
		if (_favorites_state && !favorites.contains(artist)) { continue; }

		auto item_artist = new Base::WidgetTreeItem(this, Global::Colors::tree_level_1);
		item_artist->setText(CLMN_DATE, artist);
		item_artist->setNumb(CLMN_COUNT, concerts.size());

		for (const auto concert : concerts) {
			auto item_concert = new Base::WidgetTreeItem(item_artist);
			item_concert->setText(CLMN_DATE, concert->date());
			item_concert->setText(CLMN_ARTISTS, concert->artistsAndDescriptionToString(QStringLiteral(" • ")));
			item_concert->setToolTip(CLMN_ARTISTS, concert->summaryString());
			item_concert->setText(CLMN_COUNTRY, concert->country());
			item_concert->setText(CLMN_CITY, concert->city());
			item_concert->setText(CLMN_PLACE, Helper::startWithCapital(concert->place()));
			item_concert->setId(concert->id());
		}
	}
}

void Concerts::WidgetDataList::showByTags(const DataList& data_list, const Base::ExtraList& extra_list)
{
	enum Columns {CLMN_DATE, CLMN_COUNT, CLMN_ARTISTS, CLMN_COUNTRY, CLMN_CITY, CLMN_PLACE};
	initColumns({tr("Тип / Дата"), tr("К-во"), tr("Группы"), tr("Страна"), tr("Город"), tr("Место")},
				{WIDTH_DATE_SMALL, WIDTH_COUNT, WIDTH_ARTISTS, WIDTH_COUNTRY, WIDTH_CITY, WIDTH_PLACE});
	initSorting(CLMN_DATE);

	for (const auto& extra : extra_list) {
		if (extra.group() == tr("[Теги]")) {
			auto name = extra.notes();
			auto tags = extra.title().split(", ", Qt::SkipEmptyParts);
			auto concerts_by_tags = data_list.concertsByTags(name, tags);

			if (!concerts_by_tags.empty()) {
				for (const auto& [tag, concerts] : concerts_by_tags) {
					auto item_tag = new Base::WidgetTreeItem(this, Global::Colors::tree_level_1);
					item_tag->setText(CLMN_DATE, tag);
					item_tag->setNumb(CLMN_COUNT, concerts.size());

					for (const auto concert : concerts) {
						auto item_concert = new Base::WidgetTreeItem(item_tag);
						item_concert->setText(CLMN_DATE, concert->date());
						item_concert->setText(CLMN_ARTISTS, concert->artistsAndDescriptionToString(QStringLiteral(" • ")));
						item_concert->setToolTip(CLMN_ARTISTS, concert->summaryString());
						item_concert->setText(CLMN_COUNTRY, concert->country());
						item_concert->setText(CLMN_CITY, concert->city());
						item_concert->setText(CLMN_PLACE, Helper::startWithCapital(concert->place()));
						item_concert->setId(concert->id());
					}
				}
			}
		}
	}
}

void Concerts::WidgetDataList::showByCountries(const DataList& data_list)
{
	enum Columns {CLMN_DATE, CLMN_COUNT, CLMN_ARTISTS, CLMN_CITY, CLMN_PLACE};
	initColumns({tr("Страна / Дата"), tr("К-во"), tr("Группы"), tr("Город"), tr("Место")},
				{WIDTH_DATE_SMALL, WIDTH_COUNT, WIDTH_ARTISTS, WIDTH_CITY, WIDTH_PLACE});
	initSorting(CLMN_DATE);

	auto concerts_by_countries = data_list.concertsByCountries();

	for (const auto& [country, concerts] : concerts_by_countries) {
		auto item_country = new Base::WidgetTreeItem(this, Global::Colors::tree_level_1);
		item_country->setText(CLMN_DATE, country);
		item_country->setNumb(CLMN_COUNT, concerts.size());

		for (const auto concert : concerts) {
			auto item_concert = new Base::WidgetTreeItem(item_country);
			item_concert->setText(CLMN_DATE, concert->date());
			item_concert->setText(CLMN_ARTISTS, concert->artistsAndDescriptionToString(QStringLiteral(" • ")));
			item_concert->setToolTip(CLMN_ARTISTS, concert->summaryString());
			item_concert->setText(CLMN_CITY, concert->city());
			item_concert->setText(CLMN_PLACE, Helper::startWithCapital(concert->place()));
			item_concert->setId(concert->id());
		}
	}
}

void Concerts::WidgetDataList::showByCities(const DataList& data_list)
{
	enum Columns {CLMN_DATE, CLMN_COUNT, CLMN_ARTISTS, CLMN_PLACE};
	initColumns({tr("Город / Дата"), tr("К-во"), tr("Группы"), tr("Место")},
				{WIDTH_DATE_MEDIUM, WIDTH_COUNT, WIDTH_ARTISTS, WIDTH_PLACE});
	initSorting(CLMN_DATE);

	auto concerts_by_cities = data_list.concertsByCities();

	for (const auto& [city, concerts] : concerts_by_cities) {
		auto item_city = new Base::WidgetTreeItem(this, Global::Colors::tree_level_1);
		item_city->setText(CLMN_DATE, city);
		item_city->setNumb(CLMN_COUNT, concerts.size());

		for (const auto concert : concerts) {
			auto item_concert = new Base::WidgetTreeItem(item_city);
			item_concert->setText(CLMN_DATE, concert->date());
			item_concert->setText(CLMN_ARTISTS, concert->artistsAndDescriptionToString(QStringLiteral(" • ")));
			item_concert->setToolTip(CLMN_ARTISTS, concert->summaryString());
			item_concert->setText(CLMN_PLACE, Helper::startWithCapital(concert->place()));
			item_concert->setId(concert->id());
		}
	}
}

void Concerts::WidgetDataList::showByPlaces(const DataList& data_list, const Base::ExtraList& extra_list)
{
	enum Columns {CLMN_DATE, CLMN_COUNT, CLMN_ARTISTS};
	initColumns({tr("Место / Дата"), tr("К-во"), tr("Группы")},
				{WIDTH_DATE_BIG, WIDTH_COUNT, WIDTH_ARTISTS});
	initSorting(CLMN_DATE);

	auto favorites = _favorites_state ?
			DataList::getFavorites(tr("[Избранные места]"), extra_list) :
			DataList::Favorites();
	auto synonyms = DataList::getSynonyms(tr("[Синонимы для мест]"), extra_list);
	auto concerts_by_places = data_list.concertsByPlaces(synonyms);

	for (const auto& [place, concerts] : concerts_by_places) {
		if (_favorites_state && !favorites.contains(place)) { continue; }

		auto item_place = new Base::WidgetTreeItem(this, Global::Colors::tree_level_1);
		item_place->setText(CLMN_DATE, place);
		item_place->setNumb(CLMN_COUNT, concerts.size());

		for (const auto concert : concerts) {
			auto item_concert = new Base::WidgetTreeItem(item_place);
			item_concert->setText(CLMN_DATE, concert->date());
			item_concert->setText(CLMN_ARTISTS, concert->artistsAndDescriptionToString(QStringLiteral(" • ")));
			item_concert->setToolTip(CLMN_ARTISTS, concert->summaryString());
			item_concert->setId(concert->id());
		}
	}
}

void Concerts::WidgetDataList::showPlacesTree(const DataList& data_list, const Base::ExtraList& extra_list)
{
	enum Columns {CLMN_DATE, CLMN_COUNT, CLMN_ARTISTS};
	initColumns({tr("Страна / Город / Место / Дата"), tr("К-во"), tr("Группы")},
				{WIDTH_DATE_BIG, WIDTH_COUNT, WIDTH_ARTISTS});
	initSorting(CLMN_DATE);

	auto synonyms = DataList::getSynonyms(tr("[Синонимы для мест]"), extra_list);
	auto concerts_by_countries = data_list.concertsByCountries();
	auto concerts_by_cities = data_list.concertsByCities();
	auto concerts_by_places = data_list.concertsByPlaces(synonyms);

	for (const auto& [country, concerts_in_country] : concerts_by_countries) {
		auto item_country = new Base::WidgetTreeItem(this, Global::Colors::tree_level_3);
		item_country->setText(CLMN_DATE, country);
		item_country->setNumb(CLMN_COUNT, concerts_in_country.size());

		auto list_of_cities = data_list.listOfCities(country);
		for (const auto& city : list_of_cities) {
			const auto& concerts_in_city = concerts_by_cities[country + ", " + city];
			auto item_city = new Base::WidgetTreeItem(item_country, Global::Colors::tree_level_2);
			item_city->setText(CLMN_DATE, city);
			item_city->setNumb(CLMN_COUNT, concerts_in_city.size());

			auto list_of_places = data_list.listOfPlaces(city, synonyms);
			for (const auto& place : list_of_places) {
				const auto& concerts_in_place = concerts_by_places[country + ", " + city + ", " + place];
				auto item_place = new Base::WidgetTreeItem(item_city, Global::Colors::tree_level_1);
				item_place->setText(CLMN_DATE, Helper::startWithCapital(place));
				item_place->setNumb(CLMN_COUNT, concerts_in_place.size());

				for (const auto concert : concerts_in_place) {
					auto item_concert = new Base::WidgetTreeItem(item_place);
					item_concert->setText(CLMN_DATE, concert->date());
					item_concert->setText(CLMN_ARTISTS, concert->artistsAndDescriptionToString(QStringLiteral(" • ")));
					item_concert->setToolTip(CLMN_ARTISTS, concert->summaryString());
					item_concert->setId(concert->id());
				}
			}
		}
	}
}

void Concerts::WidgetDataList::showSimple(const DataList& data_list)
{
	enum Columns {CLMN_DATE, CLMN_ARTISTS, CLMN_COUNTRY, CLMN_CITY, CLMN_PLACE};
	initColumns({tr("Дата"), tr("Группы"), tr("Страна"), tr("Город"), tr("Место")},
				{WIDTH_DATE_SMALL, WIDTH_ARTISTS, WIDTH_COUNTRY, WIDTH_CITY, WIDTH_PLACE});
	initSorting(CLMN_DATE);

	for (const auto& concert : data_list) {
		auto item_concert = new Base::WidgetTreeItem(this);
		item_concert->setText(CLMN_DATE, concert.date());
		item_concert->setText(CLMN_ARTISTS, concert.artistsAndDescriptionToString(QStringLiteral(" • ")));
		item_concert->setToolTip(CLMN_ARTISTS, concert.summaryString());
		item_concert->setText(CLMN_COUNTRY, concert.country());
		item_concert->setText(CLMN_CITY, concert.city());
		item_concert->setText(CLMN_PLACE, Helper::startWithCapital(concert.place()));
		item_concert->setId(concert.id());
	}
}
