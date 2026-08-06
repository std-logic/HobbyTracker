#include "BikeTripList.h"

#include <unordered_set>

Bike::TripList::Summary Bike::TripList::summary() const
{
	Summary sum;
	std::unordered_set<QString> list_of_countries;
	for (const auto& data : _data_list) {
		sum.total_dist += data.dist();
		sum.total_time += data.time();
		auto countries = data.countries();
		for (const auto& country : countries) { list_of_countries.insert(country); }
	}
	sum.trips_num = _data_list.size();
	sum.countries_num = list_of_countries.size();
	return sum;
}

Bike::TripList::NumbersByStrings Bike::TripList::numbersByYears(uint32_t step,
		RangeTypes range_type, uint32_t required_min, uint32_t required_max) const
{
	return numbersInRange(step, range_type, required_min, required_max,
			[](const Trip& trip) { return trip.year(); },
			[](uint32_t val, uint32_t step) { return Helper::epochString(val, step); });
}
