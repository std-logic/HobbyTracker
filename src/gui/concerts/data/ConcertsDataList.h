#pragma once

#include "ConcertsData.h"

#include <gui/base/data/BaseDataList.h>

namespace Concerts
{

class DataList : public Base::DataList<Data>
{
public:
	DataList() = default;

	struct Summary
	{
		uint32_t min_year = Global::undefined_value;
		uint32_t max_year = Global::undefined_value;
		uint32_t concerts_num = 0;
		uint32_t artists_num = 0;
		uint32_t countries_num = 0;
		uint32_t cities_num = 0;
		uint32_t places_num = 0;
	};
	Summary summary() const;

	SublistsByStrings concertsByYears(uint32_t step = 1) const;
	NumbersByStrings numbersByYears(uint32_t step = 1,
			RangeTypes range_type = RangeTypes::Discrete,
			uint32_t required_min = 0, uint32_t required_max = 0) const;

	SublistsByStrings concertsByArtists() const;
	ListOfStrings listOfArtists() const;

	ListOfStrings listOfDescriptions() const;

	SublistsByStrings concertsByCountries() const;
	ListOfStrings listOfCountries() const;

	SublistsByStrings concertsByCities() const;
	ListOfStrings listOfCities(const QString& country) const;

	SublistsByStrings concertsByPlaces() const;
	ListOfStrings listOfPlaces(const QString& city) const;
};

} // namespace Concerts
