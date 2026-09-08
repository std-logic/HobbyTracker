#include "BikeWidgetTripList.h"
#include "../common/BikeCommon.h"
#include "../data/BikeTripList.h"

#include <gui/base/widgets/BaseWidgetTreeItem.h>

Bike::WidgetTripList::WidgetTripList(QWidget* parent)
	: Base::WidgetTree{parent}
{
}

void Bike::WidgetTripList::update(const TripList& trip_list)
{
	clear();
	setRootIsDecorated(static_cast<DataListViewModes>(_view_mode) != DataListViewModes::Simple);
	switch (static_cast<DataListViewModes>(_view_mode)) {
		case DataListViewModes::Simple:			showSimple(trip_list);			break;
		case DataListViewModes::ByCountries:	showByCountries(trip_list);		break;
		default: return;
	}
	updateSearch();
}

void Bike::WidgetTripList::showSimple(const TripList& trip_list)
{
	enum Columns {CLMN_DATE, CLMN_TIME, CLMN_DIST, CLMN_COUNTRIES, CLMN_PLACES};
	setSearchColumns({CLMN_COUNTRIES, CLMN_PLACES});
	initColumns({tr("Даты"), tr("Ночёвок"), tr("Километров"), tr("Страны"), tr("Места")},
				{WIDTH_DATE, WIDTH_TIME, WIDTH_DIST, WIDTH_COUNTRIES, WIDTH_PLACES});
	initSorting(CLMN_DATE, Qt::DescendingOrder);

	for (const auto& trip : trip_list) {
		auto item_trip = new Base::WidgetTreeItem(this);
		item_trip->setText(CLMN_DATE, trip.dates());
		item_trip->setNumb(CLMN_TIME, trip.time());
		item_trip->setNumb(CLMN_DIST, trip.dist());
		item_trip->setText(CLMN_COUNTRIES, trip.countriesToString(QStringLiteral(" • ")));
		item_trip->setText(CLMN_PLACES, trip.placesToString(QStringLiteral(" → ")));
		item_trip->setHoveredToolTip(trip.summaryString());
		item_trip->setId(trip.id());
	}
}

void Bike::WidgetTripList::showByCountries(const TripList& trip_list)
{
	enum Columns {CLMN_DATE, CLMN_COUNT, CLMN_TIME, CLMN_DIST,
				  CLMN_COUNTRIES, CLMN_PLACES};
	setSearchColumns({CLMN_COUNTRIES, CLMN_PLACES});
	initColumns({tr("Страна / Даты"), tr("К-во"), tr("Ночёвок"), tr("Километров"),
				 tr("Страны"), tr("Места")},
				{WIDTH_DATE, WIDTH_COUNT, WIDTH_TIME, WIDTH_DIST,
				 WIDTH_COUNTRIES, WIDTH_PLACES});
	initSorting(CLMN_DATE);

	auto trips_by_countries = trip_list.tripsByCountries();

	for (const auto& [country, trips] : trips_by_countries) {
		auto item_country = new Base::WidgetTreeItem(this, Global::Colors::tree_level_1);
		item_country->setCountry(CLMN_DATE, country);
		item_country->setNumb(CLMN_COUNT, trips.size());
		uint32_t country_time = 0, country_dist = 0;

		for (const auto trip : trips) {
			auto item_trip = new Base::WidgetTreeItem(item_country);
			item_trip->setText(CLMN_DATE, trip->dates());
			item_trip->setNumb(CLMN_TIME, trip->time());
			item_trip->setNumb(CLMN_DIST, trip->dist());
			item_trip->setText(CLMN_COUNTRIES, trip->countriesToString(QStringLiteral(" • ")));
			item_trip->setText(CLMN_PLACES, trip->placesToString(QStringLiteral(" → ")));
			item_trip->setHoveredToolTip(trip->summaryString());
			item_trip->setId(trip->id());
			country_time += trip->time();
			country_dist += trip->dist();
		}

		item_country->setNumb(CLMN_TIME, country_time);
		item_country->setNumb(CLMN_DIST, country_dist);
	}
}
