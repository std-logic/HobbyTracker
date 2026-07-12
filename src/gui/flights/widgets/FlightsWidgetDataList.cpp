#include "FlightsWidgetDataList.h"
#include "../common/FlightsCommon.h"
#include "../data/FlightsDataList.h"

#include <gui/base/widgets/BaseWidgetTreeItem.h>

Flights::WidgetDataList::WidgetDataList(QWidget* parent)
	: Base::WidgetTree{parent}
{
}

void Flights::WidgetDataList::update(const DataList& data_list)
{
	clear();
	setRootIsDecorated(static_cast<DataListViewModes>(_view_mode) != DataListViewModes::Simple);
	switch (static_cast<DataListViewModes>(_view_mode)) {
		case DataListViewModes::ByYears:		showByYears(data_list);			break;
		case DataListViewModes::ByCountries:	showByCountries(data_list);		break;
		case DataListViewModes::ByCities:		showByCities(data_list);		break;
		case DataListViewModes::ByAirports:		showByAirports(data_list);		break;
		case DataListViewModes::Simple:			showSimple(data_list);			break;
		default: return;
	}
}

void Flights::WidgetDataList::showByYears(const DataList& data_list)
{
	enum Columns {CLMN_DATE, CLMN_COUNT, CLMN_POINTS};
	initColumns({tr("Год / Дата"), tr("К-во"), tr("Маршрут")},
				{WIDTH_DATE, WIDTH_COUNT, WIDTH_POINTS});
	initSorting(CLMN_DATE);

	auto flights_by_years = data_list.flightsByYears();

	for (const auto& [year, flights] : flights_by_years) {
		auto item_year = new Base::WidgetTreeItem(this, Global::Colors::tree_level_1);
		item_year->setText(CLMN_DATE, year);
		item_year->setNumb(CLMN_COUNT, DataList::flightsNumInSublist(flights));

		for (const auto flight : flights) {
			auto item_flight = new Base::WidgetTreeItem(item_year);
			item_flight->setText(CLMN_DATE, flight->date());
			item_flight->setText(CLMN_POINTS, flight->pointsToString());
			item_flight->setId(flight->id());
		}
	}
}

void Flights::WidgetDataList::showByCountries(const DataList& data_list)
{
	enum Columns {CLMN_DATE, CLMN_COUNT, CLMN_POINTS};
	initColumns({tr("Страна / Дата"), tr("К-во"), tr("Маршрут")},
				{WIDTH_DATE, WIDTH_COUNT, WIDTH_POINTS});
	initSorting(CLMN_DATE);

	auto flights_by_countries = data_list.flightsByCountries();

	for (const auto& [country, flights] : flights_by_countries) {
		auto item_country = new Base::WidgetTreeItem(this, Global::Colors::tree_level_1);
		item_country->setText(CLMN_DATE, country);
		item_country->setNumb(CLMN_COUNT, DataList::countryNumInSublist(country, flights));

		for (const auto flight : flights) {
			auto item_flight = new Base::WidgetTreeItem(item_country);
			item_flight->setText(CLMN_DATE, flight->date());
			item_flight->setText(CLMN_POINTS, flight->pointsToString());
			item_flight->setId(flight->id());
		}
	}
}

void Flights::WidgetDataList::showByCities(const DataList& data_list)
{
	enum Columns {CLMN_DATE, CLMN_COUNT, CLMN_POINTS};
	initColumns({tr("Город / Дата"), tr("К-во"), tr("Маршрут")},
				{WIDTH_DATE, WIDTH_COUNT, WIDTH_POINTS});
	initSorting(CLMN_DATE);

	auto flights_by_cities = data_list.flightsByCities();

	for (const auto& [city, flights] : flights_by_cities) {
		auto item_city = new Base::WidgetTreeItem(this, Global::Colors::tree_level_1);
		item_city->setText(CLMN_DATE, city);
		item_city->setNumb(CLMN_COUNT, DataList::cityNumInSublist(city.section(", ", -1), flights));

		for (const auto flight : flights) {
			auto item_flight = new Base::WidgetTreeItem(item_city);
			item_flight->setText(CLMN_DATE, flight->date());
			item_flight->setText(CLMN_POINTS, flight->pointsToString());
			item_flight->setId(flight->id());
		}
	}
}

void Flights::WidgetDataList::showByAirports(const DataList& data_list)
{
	enum Columns {CLMN_DATE, CLMN_COUNT, CLMN_POINTS};
	initColumns({tr("Аэропорт / Дата"), tr("К-во"), tr("Маршрут")},
				{WIDTH_DATE, WIDTH_COUNT, WIDTH_POINTS});
	initSorting(CLMN_DATE);

	auto flights_by_airports = data_list.flightsByAirports();

	for (const auto& [airport, flights] : flights_by_airports) {
		auto item_airport = new Base::WidgetTreeItem(this, Global::Colors::tree_level_1);
		item_airport->setText(CLMN_DATE, airport);
		item_airport->setNumb(CLMN_COUNT, DataList::airportNumInSublist(airport.section(", ", -1), flights));

		for (const auto flight : flights) {
			auto item_flight = new Base::WidgetTreeItem(item_airport);
			item_flight->setText(CLMN_DATE, flight->date());
			item_flight->setText(CLMN_POINTS, flight->pointsToString());
			item_flight->setId(flight->id());
		}
	}
}

void Flights::WidgetDataList::showSimple(const DataList& data_list)
{
	enum Columns {CLMN_DATE, CLMN_POINTS};
	initColumns({tr("Дата"), tr("Маршрут")},
				{WIDTH_DATE, WIDTH_POINTS});
	initSorting(CLMN_DATE);

	for (const auto& flight : data_list) {
		auto item_flight = new Base::WidgetTreeItem(this);
		item_flight->setText(CLMN_DATE, flight.date());
		item_flight->setText(CLMN_POINTS, flight.pointsToString());
		item_flight->setId(flight.id());
	}
}
