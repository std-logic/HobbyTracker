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
	Summary summary(bool favorites_only = false) const;

	void setFavorites(const DataList& favorites_list);
	DataList getFavorites() const;

	SublistsByStrings moviesByKinds(bool favorites_only = false) const;
	ListOfStrings listOfKinds() const;

	SublistsByStrings moviesByGenres(bool favorites_only = false) const;
	NumbersByStringsVec numbersByGenres(size_t max_num, bool favorites_only = false) const;
	ListOfStrings listOfGenres() const;

	SublistsByStrings moviesByCountries(bool favorites_only = false) const;
	NumbersByStringsVec numbersByCountries(size_t max_num, bool favorites_only = false) const;
	ListOfStrings listOfCountries() const;

	SublistsByStrings moviesByDirectors(bool favorites_only = false) const;
	NumbersByStringsVec numbersByDirectors(size_t max_num, bool favorites_only = false) const;
	ListOfStrings listOfDirectors() const;

	SublistsByStrings moviesByWriters(bool favorites_only = false) const;
	NumbersByStringsVec numbersByWriters(size_t max_num, bool favorites_only = false) const;
	ListOfStrings listOfWriters() const;

	SublistsByStrings moviesByActors(bool favorites_only = false) const;
	NumbersByStringsVec numbersByActors(size_t max_num, bool favorites_only = false) const;
	ListOfStrings listOfActors() const;

	SublistsByStrings moviesByYears(uint32_t step = 1, bool favorites_only = false) const;
	NumbersByStrings numbersByYears(uint32_t step = 1,
			RangeTypes range_type = RangeTypes::Discrete,
			uint32_t required_min = 0, uint32_t required_max = 0,
			bool favorites_only = false) const;

	SublistsByIntegers moviesByRatings(bool favorites_only = false) const;
	NumbersByIntegers numbersByRatings(bool favorites_only = false) const;

	NumbersByIntegers numbersByViewDates(bool favorites_only = false) const;
};

} // namespace Movies
