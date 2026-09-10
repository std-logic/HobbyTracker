#include "BikeTripList.h"

Bike::TripList::Summary Bike::TripList::summary() const
{
	Summary sum;
	for (const auto& data : _data_list) {
		sum.total_dist += data.dist();
		sum.total_time += data.time();
		auto countries = data.countries();
		for (const auto& country : countries) { sum.list_of_countries.insert(country); }
	}
	sum.trips_num = _data_list.size();
	sum.countries_num = sum.list_of_countries.size();
	return sum;
}

void Bike::TripList::sort()
{
	std::ranges::sort(_data_list, {}, &Trip::dateStart);
}

Bike::TripList::NumbersByStrings Bike::TripList::numbersByYears(uint32_t step,
		RangeTypes range_type, uint32_t required_min, uint32_t required_max) const
{
	return numbersInRange(step, range_type, required_min, required_max,
			[](const Trip& trip) { return trip.year(); },
			[](uint32_t val, uint32_t step) { return Helper::epochString(val, step); });
}

Bike::TripList::SublistsByStrings Bike::TripList::tripsByCountries() const
{
	return sublistsByStrings(&Trip::countries);
}

Bike::TripList::NumbersByStringsVec Bike::TripList::numbersByCountries(size_t max_num) const
{
	return sortedVec(numbersByStrings(&Trip::countries), max_num);
}
