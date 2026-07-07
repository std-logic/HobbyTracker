#include "BikeDataList.h"

Bike::DataList::Summary Bike::DataList::summary() const
{
	Summary sum;
	for (const auto& data : _data_list) {
		Helper::checkMinMax(data.year(), &sum.min_year, &sum.max_year);
		sum.total_dist += data.dist();
		sum.total_time += data.time();
	}
	if (!_data_list.empty()) {
		sum.avg_dist = static_cast<double>(sum.total_dist) / _data_list.size();
		sum.avg_time = static_cast<double>(sum.total_time) / _data_list.size();
	}
	return sum;
}

Bike::DataList::NumbersByIntegers Bike::DataList::distByYears() const
{
	return numbersByIntegers(&Data::year, &Data::dist);
}

Bike::DataList::NumbersByIntegers Bike::DataList::timeByYears() const
{
	return numbersByIntegers(&Data::year, &Data::time);
}
