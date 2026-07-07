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
	SublistsByStrings list;
	for (const auto& data : _data_list) {
		list[data.series()].push_back(&data);
	}
	return list;
}

Games::DataList::ListOfStrings Games::DataList::listOfSeries() const
{
	ListOfStrings list;
	for (const auto& data : _data_list) {
		list.insert(data.series());
	}
	return list;
}

Games::DataList::SublistsByStrings Games::DataList::gamesByDevelopers() const
{
	SublistsByStrings list;
	for (const auto& data : _data_list) {
		list[data.developer()].push_back(&data);
	}
	return list;
}

Games::DataList::ListOfStrings Games::DataList::listOfDevelopers() const
{
	ListOfStrings list;
	for (const auto& data : _data_list) {
		list.insert(data.developer());
	}
	return list;
}

Games::DataList::SublistsByStrings Games::DataList::gamesByGenres() const
{
	SublistsByStrings list;
	for (const auto& data : _data_list) {
		list[data.genre()].push_back(&data);
	}
	return list;
}

Games::DataList::ListOfStrings Games::DataList::listOfGenres() const
{
	ListOfStrings list;
	for (const auto& data : _data_list) {
		list.insert(data.genre());
	}
	return list;
}

Games::DataList::SublistsByStrings Games::DataList::gamesByYears(uint32_t step) const
{
	SublistsByStrings list;
	for (const auto& data : _data_list) {
		list[Helper::epochString(data.year(), step)].push_back(&data);
	}
	return list;
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
	SublistsByIntegers list;
	for (const auto& data : _data_list) {
		list[data.rating()].push_back(&data);
	}
	return list;
}

Games::DataList::NumbersByIntegers Games::DataList::numbersByRatings() const
{
	NumbersByIntegers list;
	for (const auto& data : _data_list) {
		++list[data.rating()];
	}
	return list;
}
