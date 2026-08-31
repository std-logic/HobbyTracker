#include "FlightsWidgetDataList.h"
#include "../common/FlightsCommon.h"
#include "../data/FlightsDataList.h"

#include <gui/base/widgets/BaseWidgetTreeItem.h>

#include <common/Regions.h>

#include <QDate>

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
		case DataListViewModes::ByRegions:		showByRegions(data_list);		break;
		case DataListViewModes::ByCountries:	showByCountries(data_list);		break;
		case DataListViewModes::ByCities:		showByCities(data_list);		break;
		case DataListViewModes::ByAirports:		showByAirports(data_list);		break;
		case DataListViewModes::ByRoutes:		showByRoutes(data_list);		break;
		case DataListViewModes::AirportsTree:	showAirportsTree(data_list);	break;
		case DataListViewModes::Simple:			showSimple(data_list);			break;
		default: return;
	}
}

void Flights::WidgetDataList::showByYears(const DataList& data_list)
{
	enum Columns {CLMN_DATE, CLMN_COUNT, CLMN_DIST, CLMN_POINTS};
	initColumns({tr("Год / Дата"), tr("К-во"), tr("Километров"), tr("Маршрут")},
				{WIDTH_DATE, WIDTH_COUNT, WIDTH_DIST, WIDTH_POINTS});
	initSorting(CLMN_DATE, Qt::DescendingOrder);

	auto flights_by_years = data_list.flightsByYears();
	auto curr_year = QString::number(QDate::currentDate().year());

	for (const auto& [year, flights] : flights_by_years) {
		auto item_year = new Base::WidgetTreeItem(this, Global::Colors::tree_level_1);
		item_year->setText(CLMN_DATE, year);
		item_year->setNumb(CLMN_COUNT, DataList::flightsNumInSublist(flights));
		item_year->setNumb(CLMN_DIST, DataList::distInSublist(flights));
		if (year == curr_year) { item_year->setExpanded(true); }

		for (const auto flight : flights) {
			auto item_flight = new Base::WidgetTreeItem(item_year);
			item_flight->setText(CLMN_DATE, flight->date());
			item_flight->setNumb(CLMN_DIST, flight->distTotal());
			item_flight->setText(CLMN_POINTS, flight->pointsToString());
			item_flight->setId(flight->id());
		}
	}
}

void Flights::WidgetDataList::showByRegions(const DataList& data_list)
{
	enum Columns {CLMN_DATE, CLMN_COUNT, CLMN_DIST, CLMN_POINTS};
	initColumns({tr("Регион / Страна / Дата"), tr("К-во"), tr("Километров"), tr("Маршрут")},
				{WIDTH_DATE, WIDTH_COUNT, WIDTH_DIST, WIDTH_POINTS});
	initSorting(CLMN_DATE);

	auto flights_by_regions = data_list.flightsByRegions();

	for (const auto& [region, flights_by_countries] : flights_by_regions) {
		auto item_region = new Base::WidgetTreeItem(this, Global::Colors::tree_level_2);
		item_region->setText(CLMN_DATE, region);
		uint32_t region_flights_num = 0;
		std::unordered_set<QString> present_countries;

		for (const auto& [country, flights] : flights_by_countries) {
			auto item_country = new Base::WidgetTreeItem(item_region, Global::Colors::tree_level_1);
			item_country->setText(CLMN_DATE, country);
			uint32_t country_flights_num = DataList::countryNumInSublist(country, flights);
			region_flights_num += country_flights_num;
			item_country->setNumb(CLMN_COUNT, country_flights_num);
			present_countries.insert(country);

			for (const auto flight : flights) {
				auto item_flight = new Base::WidgetTreeItem(item_country);
				item_flight->setText(CLMN_DATE, flight->date());
				item_flight->setNumb(CLMN_DIST, flight->distTotal());
				item_flight->setText(CLMN_POINTS, flight->pointsToString());
				item_flight->setId(flight->id());
			}
		}

		item_region->setNumb(CLMN_COUNT, region_flights_num);
		item_region->setToolTipEverywhere(Regions::progress(region, present_countries));
	}
}

void Flights::WidgetDataList::showByCountries(const DataList& data_list)
{
	enum Columns {CLMN_DATE, CLMN_COUNT, CLMN_DIST, CLMN_POINTS};
	initColumns({tr("Страна / Дата"), tr("К-во"), tr("Километров"), tr("Маршрут")},
				{WIDTH_DATE, WIDTH_COUNT, WIDTH_DIST, WIDTH_POINTS});
	initSorting(CLMN_DATE);

	auto flights_by_countries = data_list.flightsByCountries();

	for (const auto& [country, flights] : flights_by_countries) {
		auto item_country = new Base::WidgetTreeItem(this, Global::Colors::tree_level_1);
		item_country->setText(CLMN_DATE, country);
		item_country->setNumb(CLMN_COUNT, DataList::countryNumInSublist(country, flights));

		for (const auto flight : flights) {
			auto item_flight = new Base::WidgetTreeItem(item_country);
			item_flight->setText(CLMN_DATE, flight->date());
			item_flight->setNumb(CLMN_DIST, flight->distTotal());
			item_flight->setText(CLMN_POINTS, flight->pointsToString());
			item_flight->setId(flight->id());
		}
	}
}

void Flights::WidgetDataList::showByCities(const DataList& data_list)
{
	enum Columns {CLMN_DATE, CLMN_COUNT, CLMN_DIST, CLMN_POINTS};
	initColumns({tr("Город / Дата"), tr("К-во"), tr("Километров"), tr("Маршрут")},
				{WIDTH_DATE, WIDTH_COUNT, WIDTH_DIST, WIDTH_POINTS});
	initSorting(CLMN_DATE);

	auto flights_by_cities = data_list.flightsByCities();

	for (const auto& [city, flights] : flights_by_cities) {
		auto item_city = new Base::WidgetTreeItem(this, Global::Colors::tree_level_1);
		item_city->setText(CLMN_DATE, city);
		item_city->setNumb(CLMN_COUNT, DataList::cityNumInSublist(city.section(", ", -1), flights));

		for (const auto flight : flights) {
			auto item_flight = new Base::WidgetTreeItem(item_city);
			item_flight->setText(CLMN_DATE, flight->date());
			item_flight->setNumb(CLMN_DIST, flight->distTotal());
			item_flight->setText(CLMN_POINTS, flight->pointsToString());
			item_flight->setId(flight->id());
		}
	}
}

void Flights::WidgetDataList::showByAirports(const DataList& data_list)
{
	enum Columns {CLMN_DATE, CLMN_COUNT, CLMN_DIST, CLMN_POINTS};
	initColumns({tr("Аэропорт / Дата"), tr("К-во"), tr("Километров"), tr("Маршрут")},
				{WIDTH_DATE, WIDTH_COUNT, WIDTH_DIST, WIDTH_POINTS});
	initSorting(CLMN_DATE);

	auto flights_by_airports = data_list.flightsByAirports();

	for (const auto& [airport, flights] : flights_by_airports) {
		auto item_airport = new Base::WidgetTreeItem(this, Global::Colors::tree_level_1);
		item_airport->setText(CLMN_DATE, airport);
		item_airport->setNumb(CLMN_COUNT, DataList::airportNumInSublist(airport.section(", ", -1), flights));

		for (const auto flight : flights) {
			auto item_flight = new Base::WidgetTreeItem(item_airport);
			item_flight->setText(CLMN_DATE, flight->date());
			item_flight->setNumb(CLMN_DIST, flight->distTotal());
			item_flight->setText(CLMN_POINTS, flight->pointsToString());
			item_flight->setId(flight->id());
		}
	}
}

void Flights::WidgetDataList::showByRoutes(const DataList& data_list)
{
	enum Columns {CLMN_DATE, CLMN_COUNT, CLMN_DIST, CLMN_POINTS};
	initColumns({tr("Маршрут / Дата"), tr("К-во"), tr("Километров"), tr("Маршрут")},
				{WIDTH_ROUTE, WIDTH_COUNT, WIDTH_DIST, WIDTH_POINTS});
	initSorting(CLMN_DATE);

	auto flights_by_routes = data_list.flightsByRoutes();

	for (const auto& [route, flights] : flights_by_routes) {
		auto item_route = new Base::WidgetTreeItem(this, Global::Colors::tree_level_1);
		item_route->setText(CLMN_DATE, route);
		item_route->setNumb(CLMN_COUNT, flights.size());

		for (const auto flight : flights) {
			auto item_flight = new Base::WidgetTreeItem(item_route);
			item_flight->setText(CLMN_DATE, flight->date());
			item_flight->setNumb(CLMN_DIST, flight->distTotal());
			item_flight->setText(CLMN_POINTS, flight->pointsToString());
			item_flight->setId(flight->id());
		}
	}
}

void Flights::WidgetDataList::showAirportsTree(const DataList& data_list)
{
	enum Columns {CLMN_DATE, CLMN_COUNT, CLMN_DIST, CLMN_POINTS};
	initColumns({tr("Страна / Город / Аэропорт / Дата"), tr("К-во"), tr("Километров"), tr("Маршрут")},
				{WIDTH_DATE, WIDTH_COUNT, WIDTH_DIST, WIDTH_POINTS});
	initSorting(CLMN_DATE);

	auto flights_by_countries = data_list.flightsByCountries();
	auto flights_by_cities = data_list.flightsByCities();
	auto flights_by_airports = data_list.flightsByAirports();

	for (const auto& [country, flights_in_country] : flights_by_countries) {
		auto item_country = new Base::WidgetTreeItem(this, Global::Colors::tree_level_3);
		item_country->setText(CLMN_DATE, country);
		item_country->setNumb(CLMN_COUNT, DataList::countryNumInSublist(country, flights_in_country));

		auto list_of_cities = data_list.listOfCities(country);
		for (const auto& city : list_of_cities) {
			const auto& flights_in_city = flights_by_cities[country + ", " + city];
			auto item_city = new Base::WidgetTreeItem(item_country, Global::Colors::tree_level_2);
			item_city->setText(CLMN_DATE, city);
			item_city->setNumb(CLMN_COUNT, DataList::cityNumInSublist(city, flights_in_city));

			auto list_of_airports = data_list.listOfAirports(city);
			for (const auto& airport : list_of_airports) {
				const auto& flights_in_airport = flights_by_airports[country + ", " + city + ", " + airport];
				auto item_airport = new Base::WidgetTreeItem(item_city, Global::Colors::tree_level_1);
				item_airport->setText(CLMN_DATE, airport);
				item_airport->setNumb(CLMN_COUNT, DataList::airportNumInSublist(airport, flights_in_airport));

				for (const auto flight : flights_in_airport) {
					auto item_flight = new Base::WidgetTreeItem(item_airport);
					item_flight->setText(CLMN_DATE, flight->date());
					item_flight->setNumb(CLMN_DIST, flight->distTotal());
					item_flight->setText(CLMN_POINTS, flight->pointsToString());
					item_flight->setId(flight->id());
				}
			}
		}
	}
}

void Flights::WidgetDataList::showSimple(const DataList& data_list)
{
	enum Columns {CLMN_DATE, CLMN_DIST, CLMN_POINTS};
	initColumns({tr("Дата"), tr("Километров"), tr("Маршрут")},
				{WIDTH_DATE, WIDTH_DIST, WIDTH_POINTS});
	initSorting(CLMN_DATE, Qt::DescendingOrder);

	for (const auto& flight : data_list) {
		auto item_flight = new Base::WidgetTreeItem(this);
		item_flight->setText(CLMN_DATE, flight.date());
		item_flight->setNumb(CLMN_DIST, flight.distTotal());
		item_flight->setText(CLMN_POINTS, flight.pointsToString());
		item_flight->setId(flight.id());
	}
}
