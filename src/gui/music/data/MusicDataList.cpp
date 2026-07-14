#include "MusicDataList.h"

#include <unordered_set>

Music::DataList::Summary Music::DataList::summary() const
{
	Summary sum;
	std::unordered_set<QString> list_of_genres, list_of_countries;
	for (const auto& data : _data_list) {
		list_of_genres.insert(data.genre());
		list_of_countries.insert(data.country());
		Helper::checkMinMax(data.year(), &sum.min_year, &sum.max_year);
		if (data.isActive()) { ++sum.actives_num; }
	}
	sum.artists_num = _data_list.size();
	sum.genres_num = list_of_genres.size();
	sum.countries_num = list_of_countries.size();
	return sum;
}

Music::DataList::SublistsByStrings Music::DataList::artistsByGenres() const
{
	return sublistsByStrings(&Data::genre);
}

Music::DataList::ListOfStrings Music::DataList::listOfGenres() const
{
	return listOfStrings(&Data::genre);
}

Music::DataList::SublistsByStrings Music::DataList::artistsByCountries() const
{
	return sublistsByStrings(&Data::country);
}

Music::DataList::ListOfStrings Music::DataList::listOfCountries() const
{
	return listOfStrings(&Data::country);
}

Music::DataList::SublistsByStrings Music::DataList::artistsByYears(uint32_t step) const
{
	return sublistsByEpochStrings(&Data::year, step);
}

Music::DataList::NumbersByStrings Music::DataList::numbersByYears(uint32_t step,
		RangeTypes range_type, uint32_t required_min, uint32_t required_max) const
{
	return numbersInRange(step, range_type, required_min, required_max,
			[](const Data& data) { return data.year(); },
			[](uint32_t val, uint32_t step) { return Helper::epochString(val, step); });
}

Music::DataList::SublistsByIntegers Music::DataList::artistsByStates() const
{
	return sublistsByIntegers(&Data::state);
}

Music::DataList::NumbersByIntegers Music::DataList::numbersByStates() const
{
	return numbersByIntegers(&Data::state);
}
