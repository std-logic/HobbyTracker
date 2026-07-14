#pragma once

#include "MusicData.h"

#include <gui/base/data/BaseDataList.h>

namespace Music
{

class DataList : public Base::DataList<Data>
{
public:
	DataList() = default;

	struct Summary
	{
		int artists_num = 0;
		int actives_num = 0;
		int genres_num = 0;
		int countries_num = 0;
		uint32_t min_year = Global::undefined_value;
		uint32_t max_year = Global::undefined_value;
	};
	Summary summary() const;

	SublistsByStrings artistsByGenres() const;
	ListOfStrings listOfGenres() const;

	SublistsByStrings artistsByCountries() const;
	ListOfStrings listOfCountries() const;

	SublistsByStrings artistsByYears(uint32_t step = 1) const;
	NumbersByStrings numbersByYears(uint32_t step = 1,
			RangeTypes range_type = RangeTypes::Discrete,
			uint32_t required_min = 0, uint32_t required_max = 0) const;

	SublistsByIntegers artistsByStates() const;
	NumbersByIntegers numbersByStates() const;
};

} // namespace Music
