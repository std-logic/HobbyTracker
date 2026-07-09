#include "BikeDataList.h"

Bike::DataList::Summary Bike::DataList::summary() const
{
	Summary sum;
	for (const auto& data : _data_list) {
		Helper::checkMinMax(data.year(), &sum.min_year, &sum.max_year);
		sum.total_dist += data.dist();
		sum.total_time += data.time();
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
