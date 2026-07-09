#pragma once

#include "TrekkingData.h"

#include <gui/base/data/BaseDataList.h>

namespace Trekking
{

class DataList : public Base::DataList<Data>
{
public:
	DataList() = default;

	struct Summary
	{
		uint32_t min_year = Global::undefined_value;
		uint32_t max_year = Global::undefined_value;
		uint32_t tracks_num = 0;
		uint32_t total_dist = 0;
		uint32_t total_time = 0;
		uint32_t highest_peak = 0;
	};
	Summary summary() const;

	NumbersByStrings numbersByYears(uint32_t step = 1,
			RangeTypes range_type = RangeTypes::Discrete,
			uint32_t required_min = 0, uint32_t required_max = 0) const;

	SublistsByStrings tracksByCountries() const;

	SublistsByStrings tracksByKinds() const;
	ListOfStrings listOfKinds() const;
};

} // namespace Trekking
