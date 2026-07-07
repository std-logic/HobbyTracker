#include "GamesDataList.h"

#include <unordered_set>

Games::DataList::Summary Games::DataList::summary() const
{
	Summary sum;
	std::unordered_set<QString> list_series, list_developers, list_genres;
	for (const auto& data : _data_list) {
		list_series.insert(data.series());
		list_developers.insert(data.developer());
		list_genres.insert(data.genre());
		Helper::checkMinMax(data.year(), &sum.min_year, &sum.max_year);
		sum.rating += data.rating();
	}
	sum.series_num = list_series.size();
	sum.games_num = _data_list.size();
	sum.developers_num = list_developers.size();
	sum.genres_num = list_genres.size();
	if (sum.games_num) { sum.rating /= sum.games_num; }
	return sum;
}

Games::DataList::SublistsByStrings Games::DataList::gamesBySeries() const
{
	return sublistsByStrings(&Data::series);
}

Games::DataList::ListOfStrings Games::DataList::listOfSeries() const
{
	return listOfStrings(&Data::series);
}

Games::DataList::SublistsByStrings Games::DataList::gamesByDevelopers() const
{
	return sublistsByStrings(&Data::developer);
}

Games::DataList::ListOfStrings Games::DataList::listOfDevelopers() const
{
	return listOfStrings(&Data::developer);
}

Games::DataList::SublistsByStrings Games::DataList::gamesByGenres() const
{
	return sublistsByStrings(&Data::genre);
}

Games::DataList::ListOfStrings Games::DataList::listOfGenres() const
{
	return listOfStrings(&Data::genre);
}

Games::DataList::SublistsByStrings Games::DataList::gamesByYears(uint32_t step) const
{
	return sublistsByEpochStrings(&Data::year, step);
}

Games::DataList::NumbersByStrings Games::DataList::numbersByYears(uint32_t step,
		RangeTypes range_type, uint32_t required_min, uint32_t required_max) const
{
	return numbersInRange(step, range_type, required_min, required_max,
			[](const Data& data) { return data.year(); },
			[](uint32_t val, uint32_t step) { return Helper::epochString(val, step); });
}

Games::DataList::SublistsByIntegers Games::DataList::gamesByRatings() const
{
	return sublistsByIntegers(&Data::rating);
}

Games::DataList::NumbersByIntegers Games::DataList::numbersByRatings() const
{
	return numbersByIntegers(&Data::rating);
}
