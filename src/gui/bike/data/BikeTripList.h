#pragma once

#include "BikeTrip.h"

#include <gui/base/data/BaseDataList.h>

namespace Bike
{

class TripList : public Base::DataList<Trip>
{
public:
	TripList() = default;

	struct Summary
	{
		uint32_t trips_num = 0;
		uint32_t total_dist = 0;
		uint32_t total_time = 0;
	};
	Summary summary() const;

	NumbersByStrings numbersByYears(uint32_t step = 1,
			RangeTypes range_type = RangeTypes::Discrete,
			uint32_t required_min = 0, uint32_t required_max = 0) const;
};

} // namespace Bike
