#include "FlightsDataList.h"

#include <unordered_set>

Flights::DataList::Summary Flights::DataList::summary() const
{
	Summary sum;
	std::unordered_set<QString> list_of_countries, list_of_cities, list_of_airports;
	for (const auto& data : _data_list) {
		Helper::checkMinMax(data.year(), &sum.min_year, &sum.max_year);
		sum.flights_num += data.flightsNum();
		for (size_t i = 0; i < data.pointsNum(); ++i) {
			list_of_countries.insert(data.country(i));
			list_of_cities.insert(data.city(i));
			list_of_airports.insert(data.airport(i));
			if (i > 0) {
				if (data.country(i) == data.country(i-1)) {
					++sum.local_num;
				}
			}
		}
	}
	sum.international_num = sum.flights_num - sum.local_num;
	sum.countries_num = list_of_countries.size();
	sum.cities_num = list_of_cities.size();
	sum.airports_num = list_of_airports.size();
	return sum;
}

Flights::DataList::SublistsByStrings Flights::DataList::flightsByYears(uint32_t step) const
{
	return sublistsByEpochStrings(&Data::year, step);
}

Flights::DataList::NumbersByStrings Flights::DataList::numbersByYears(uint32_t step,
		RangeTypes range_type, uint32_t required_min, uint32_t required_max) const
{
	return numbersInRange(step, range_type, required_min, required_max,
			[](const Data& data) { return data.year(); },
			[](const Data& data) { return data.flightsNum(); },
			[](uint32_t val, uint32_t step) { return Helper::epochString(val, step); });
}

Flights::DataList::SublistsByStrings Flights::DataList::flightsByCountries() const
{
	return sublistsByStrings(&Data::countries);
}

Flights::DataList::ListOfStrings Flights::DataList::listOfCountries() const
{
	return listOfStrings(&Data::countries);
}

Flights::DataList::SublistsByStrings Flights::DataList::flightsByCities() const
{
	return sublistsByStrings(&Data::cities);
}

Flights::DataList::ListOfStrings Flights::DataList::listOfCities(const QString& country) const
{
	ListOfStrings list;
	for (const auto& data : _data_list) {
		for (size_t i = 0; i < data.pointsNum(); ++i) {
			if (data.country(i) == country) {
				list.insert(data.city(i));
			}
		}
	}
	return list;
}

Flights::DataList::SublistsByStrings Flights::DataList::flightsByAirports() const
{
	return sublistsByStrings(&Data::airports);
}

Flights::DataList::ListOfStrings Flights::DataList::listOfAirports(const QString& city) const
{
	ListOfStrings list;
	for (const auto& data : _data_list) {
		for (size_t i = 0; i < data.pointsNum(); ++i) {
			if (data.city(i) == city) {
				list.insert(data.airport(i));
			}
		}
	}
	return list;
}

uint32_t Flights::DataList::flightsNumInSublist(const SubListContainer& sublist)
{
	uint32_t flights_num = 0;
	for (auto data : sublist) {
		flights_num += data->flightsNum();
	}
	return flights_num;
}

uint32_t Flights::DataList::countryNumInSublist(const QString& country, const SubListContainer& sublist)
{
	uint32_t country_num = 0;
	for (auto data : sublist) {
		for (size_t point = 0; point < data->pointsNum(); ++point) {
			if (data->country(point) == country) {
				++country_num;
			}
		}
	}
	return country_num;
}

uint32_t Flights::DataList::cityNumInSublist(const QString& city, const SubListContainer& sublist)
{
	uint32_t city_num = 0;
	for (auto data : sublist) {
		for (size_t point = 0; point < data->pointsNum(); ++point) {
			if (data->city(point) == city) {
				++city_num;
			}
		}
	}
	return city_num;
}

uint32_t Flights::DataList::airportNumInSublist(const QString& airport, const SubListContainer& sublist)
{
	uint32_t airport_num = 0;
	for (auto data : sublist) {
		for (size_t point = 0; point < data->pointsNum(); ++point) {
			if (data->airport(point) == airport) {
				++airport_num;
			}
		}
	}
	return airport_num;
}
