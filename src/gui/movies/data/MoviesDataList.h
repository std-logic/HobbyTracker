#pragma once

#include "MoviesData.h"

#include <gui/base/data/BaseDataList.h>

namespace Movies
{

class DataList : public Base::DataList<Data>
{
public:
	DataList() = default;

	struct Summary
	{
		uint32_t viewed_num = 0;
		uint32_t movies_num = 0;
		uint32_t series_num = 0;
		uint32_t animation_num = 0;
		uint32_t animation_series_num = 0;
		uint32_t countries_num = 0;
		uint32_t min_year = Global::undefined_value;
		uint32_t max_year = Global::undefined_value;
		double rating = 0.;
	};
	Summary summary() const;

	void setFavorites(const DataList& favorites);
	DataList getFavorites() const;

	SublistsByStrings moviesByKinds() const;
	ListOfStrings listOfKinds() const;

	SublistsByStrings moviesByGenres() const;
	ListOfStrings listOfGenres() const;

	SublistsByStrings moviesByCountries() const;
	ListOfStrings listOfCountries() const;

	SublistsByStrings moviesByDirectors() const;
	ListOfStrings listOfDirectors() const;

	SublistsByStrings moviesByWriters() const;
	ListOfStrings listOfWriters() const;

	SublistsByStrings moviesByActors() const;
	ListOfStrings listOfActors() const;

	SublistsByStrings moviesByYears(uint32_t step = 1) const;
	NumbersByStrings numbersByYears(uint32_t step = 1,
			RangeTypes range_type = RangeTypes::Discrete,
			uint32_t required_min = 0, uint32_t required_max = 0) const;

	SublistsByIntegers moviesByRatings() const;
	NumbersByIntegers numbersByRatings() const;

	NumbersByIntegers numbersByViewDates() const;
};

} // namespace Movies
