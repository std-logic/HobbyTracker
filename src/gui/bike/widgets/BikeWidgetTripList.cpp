#include "BikeWidgetTripList.h"
#include "../data/BikeTripList.h"

#include <gui/base/widgets/BaseWidgetTreeItem.h>

Bike::WidgetTripList::WidgetTripList(QWidget* parent)
	: Base::WidgetTree{parent}
{
	setRootIsDecorated(false);
}

void Bike::WidgetTripList::update(const TripList& trip_list)
{
	clear();
	showSimple(trip_list);
}

void Bike::WidgetTripList::showSimple(const TripList& trip_list)
{
	enum Columns {CLMN_DATE, CLMN_TIME, CLMN_DIST, CLMN_COUNTRIES, CLMN_PLACES};
	initColumns({tr("Даты"), tr("Ночёвок"), tr("Километров"), tr("Страны"), tr("Места")},
				{WIDTH_DATE, WIDTH_TIME, WIDTH_DIST, WIDTH_COUNTRIES, WIDTH_PLACES});
	initSorting(CLMN_DATE);

	for (const auto& trip : trip_list) {
		auto item_trip = new Base::WidgetTreeItem(this);
		item_trip->setText(CLMN_DATE, trip.dates());
		item_trip->setNumb(CLMN_TIME, trip.time());
		item_trip->setNumb(CLMN_DIST, trip.dist());
		item_trip->setText(CLMN_COUNTRIES, trip.countriesToString(QStringLiteral(" • ")));
		item_trip->setText(CLMN_PLACES, trip.placesToString(QStringLiteral(" → ")));
		item_trip->setId(trip.id());
	}
}
