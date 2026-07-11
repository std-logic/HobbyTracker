#pragma once

#include "FlightsData.h"

#include <gui/base/data/BaseDataList.h>

namespace Flights
{

class DataList : public Base::DataList<Data>
{
public:
	DataList() = default;

	struct Summary
	{
		uint32_t min_year = Global::undefined_value;
		uint32_t max_year = Global::undefined_value;
		uint32_t flights_num = 0;
		uint32_t countries_num = 0;
		uint32_t cities_num = 0;
		uint32_t airports_num = 0;
	};
	Summary summary() const;

	SublistsByStrings flightsByYears(uint32_t step = 1) const;
	NumbersByStrings numbersByYears(uint32_t step = 1,
			RangeTypes range_type = RangeTypes::Discrete,
			uint32_t required_min = 0, uint32_t required_max = 0) const;

	SublistsByStrings flightsByCountries() const;
	ListOfStrings listOfCountries() const;

	SublistsByStrings flightsByCities() const;
	ListOfStrings listOfCities(const QString& country) const;

	SublistsByStrings flightsByAirports() const;
	ListOfStrings listOfAirports(const QString& city) const;
};

} // namespace Flights
