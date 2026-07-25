#include "ConcertsDataList.h"

#include <unordered_set>

Concerts::DataList::Summary Concerts::DataList::summary() const
{
	Summary sum;
	std::unordered_set<QString> list_of_artists, list_of_countries, list_of_cities, list_of_places;
	for (const auto& data : _data_list) {
		auto artists = data.artists();
		for (const auto& artist : artists) {
			list_of_artists.insert(artist);
		}
		list_of_countries.insert(data.country());
		list_of_cities.insert(data.city());
		list_of_places.insert(data.place());
		Helper::checkMinMax(data.year(), &sum.min_year, &sum.max_year);
	}
	sum.concerts_num = _data_list.size();
	sum.artists_num = list_of_artists.size();
	sum.countries_num = list_of_countries.size();
	sum.cities_num = list_of_cities.size();
	sum.places_num = list_of_places.size();
	return sum;
}

Concerts::DataList::SublistsByStrings Concerts::DataList::concertsByYears(uint32_t step) const
{
	return sublistsByEpochStrings(&Data::year, step);
}

Concerts::DataList::NumbersByStrings Concerts::DataList::numbersByYears(uint32_t step,
		RangeTypes range_type, uint32_t required_min, uint32_t required_max) const
{
	return numbersInRange(step, range_type, required_min, required_max,
			[](const Data& data) { return data.year(); },
			[](uint32_t val, uint32_t step) { return Helper::epochString(val, step); });
}

Concerts::DataList::SublistsByStrings Concerts::DataList::concertsByArtists() const
{
	return sublistsByStrings(&Data::artists);
}

Concerts::DataList::ListOfStrings Concerts::DataList::listOfArtists() const
{
	return listOfStrings(&Data::artists);
}

Concerts::DataList::SublistsByStrings Concerts::DataList::concertsByCountries() const
{
	return sublistsByStrings(&Data::country);
}

Concerts::DataList::ListOfStrings Concerts::DataList::listOfCountries() const
{
	return listOfStrings(&Data::country);
}

Concerts::DataList::SublistsByStrings Concerts::DataList::concertsByCities() const
{
	return sublistsByStrings(&Data::city);
}

Concerts::DataList::ListOfStrings Concerts::DataList::listOfCities(const QString& country) const
{
	ListOfStrings list;
	for (const auto& data : _data_list) {
		if (data.country() == country) {
			list.insert(data.city());
		}
	}
	return list;
}

Concerts::DataList::SublistsByStrings Concerts::DataList::concertsByPlaces() const
{
	return sublistsByStrings(&Data::place);
}

Concerts::DataList::ListOfStrings Concerts::DataList::listOfPlaces(const QString& city) const
{
	ListOfStrings list;
	for (const auto& data : _data_list) {
		if (data.city() == city) {
			list.insert(data.place());
		}
	}
	return list;
}
