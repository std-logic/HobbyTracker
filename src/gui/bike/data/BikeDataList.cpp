#include "BikeDataList.h"

Bike::DataList::Summary Bike::DataList::summary() const
{
	Summary sum;
	for (const auto& data : _data_list) {
		Helper::checkMinMax(data.year(), &sum.min_year, &sum.max_year);
		sum.dist += data.dist();
		sum.time += data.time();
	}
	if (!_data_list.empty()) {
		sum.dist /= _data_list.size();
		sum.time /= _data_list.size();
	}
	return sum;
}

Bike::DataList::NumbersByIntegers Bike::DataList::distByYears() const
{
	NumbersByIntegers list;
	for (const auto& data : _data_list) {
		list[data.year()] = data.dist();
	}
	return list;
}

Bike::DataList::NumbersByIntegers Bike::DataList::timeByYears() const
{
	NumbersByIntegers list;
	for (const auto& data : _data_list) {
		list[data.year()] = data.time();
	}
	return list;
}
