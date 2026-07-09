#pragma once

#include "BikeData.h"

#include <gui/base/data/BaseDataList.h>

namespace Bike
{

class DataList : public Base::DataList<Data>
{
public:
	DataList() = default;

	struct Summary
	{
		uint32_t total_dist = 0;
		uint32_t total_time = 0;
		uint32_t min_year = Global::undefined_value;
		uint32_t max_year = Global::undefined_value;
	};
	Summary summary() const;

	NumbersByIntegers distByYears() const;
	NumbersByIntegers timeByYears() const;
};

} // namespace Bike
