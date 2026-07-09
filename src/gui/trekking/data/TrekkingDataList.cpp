#include "TrekkingDataList.h"

Trekking::DataList::Summary Trekking::DataList::summary() const
{
	Summary sum;
	for (const auto& data : _data_list) {
		Helper::checkMinMax(data.year(), &sum.min_year, &sum.max_year);
		sum.total_dist += data.dist();
		sum.total_time += data.time();
		sum.highest_peak = std::max(sum.highest_peak, data.peak());
	}
	sum.tracks_num = _data_list.size();
	return sum;
}

Trekking::DataList::NumbersByStrings Trekking::DataList::numbersByYears(uint32_t step,
		RangeTypes range_type, uint32_t required_min, uint32_t required_max) const
{
	return numbersInRange(step, range_type, required_min, required_max,
			[](const Data& data) { return data.year(); },
			[](uint32_t val, uint32_t step) { return Helper::epochString(val, step); });
}

Trekking::DataList::SublistsByStrings Trekking::DataList::tracksByCountries() const
{
	return sublistsByStrings(&Data::countries);
}

Trekking::DataList::SublistsByStrings Trekking::DataList::tracksByKinds() const
{
	return sublistsByStrings(&Data::kind);
}

Trekking::DataList::ListOfStrings Trekking::DataList::listOfKinds() const
{
	return listOfStrings(&Data::kind);
}
