#pragma once

#include "GamesData.h"

#include <gui/base/data/BaseDataList.h>

namespace Games
{

class DataList : public Base::DataList<Data>
{
public:
	DataList() = default;

	struct Summary
	{
		int series_num = 0;
		int games_num = 0;
		int genres_num = 0;
		int developers_num = 0;
		uint32_t min_year = Global::undefined_value;
		uint32_t max_year = Global::undefined_value;
		double rating = 0.;
	};
	Summary summary() const;

	SublistsByStrings gamesBySeries() const;
	ListOfStrings listOfSeries() const;

	SublistsByStrings gamesByGenres() const;
	ListOfStrings listOfGenres() const;

	SublistsByStrings gamesByDevelopers() const;
	ListOfStrings listOfDevelopers() const;

	SublistsByStrings gamesByYears(uint32_t step = 1) const;
	NumbersByStrings numbersByYears(uint32_t step = 1,
			RangeTypes range_type = RangeTypes::Discrete,
			uint32_t required_min = 0, uint32_t required_max = 0) const;

	SublistsByIntegers gamesByRatings() const;
	NumbersByIntegers numbersByRatings() const;

	static QString yearString(const SubListContainer& sublist);
};

} // namespace Games
