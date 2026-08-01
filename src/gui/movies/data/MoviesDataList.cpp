#include "MoviesDataList.h"

#include <unordered_set>
#include <unordered_map>

Movies::DataList::Summary Movies::DataList::summary() const
{
	Summary sum;
	std::unordered_set<QString> list_of_countries;
	for (const auto& data : _data_list) {
		if (data.kind() == QStringLiteral("Фильм")) { ++sum.movies_num; }
		if (data.kind() == QStringLiteral("Сериал")) { ++sum.series_num; }
		if (data.kind() == QStringLiteral("Мультфильм")) { ++sum.animation_num; }
		if (data.kind() == QStringLiteral("Мультсериал")) { ++sum.animation_series_num; }
		auto countries = data.countries();
		for (const auto& country : countries) { list_of_countries.insert(country); }
		Helper::checkMinMax(data.year(), &sum.min_year, &sum.max_year);
		sum.rating += data.rating();
	}
	sum.viewed_num = _data_list.size();
	sum.countries_num = list_of_countries.size();
	if (sum.viewed_num) { sum.rating /= sum.viewed_num; }
	return sum;
}

void Movies::DataList::setFavorites(const DataList& favorites)
{
	std::unordered_map<QString, const Data*> favorites_map;
	for (const auto& favorites_data : favorites) {
		favorites_map[favorites_data.titleTr()] = &favorites_data;
	}

	for (auto& data : _data_list) {
		if (favorites_map.contains(data.titleTr())) {
			auto favorites_data = favorites_map[data.titleTr()];
			if (data.year() == favorites_data->year()) {
				data.setFavorite(true);
				data.setTitleOrig(favorites_data->titleOrig());
				data.setGenres(favorites_data->genres());
				data.setCountries(favorites_data->countries());
				data.setDirectors(favorites_data->directors());
				data.setWriters(favorites_data->writers());
				data.setActors(favorites_data->actors());
			}
		}
	}
}

Movies::DataList Movies::DataList::getFavorites() const
{
	DataList favorites;
	for (const auto& data : _data_list) {
		if (data.isFavorite()) {
			favorites.add(data);
		}
	}
	std::ranges::sort(favorites, {}, &Data::titleTr);
	return favorites;
}

Movies::DataList::SublistsByStrings Movies::DataList::moviesByKinds() const
{
	return sublistsByStrings(&Data::kind);
}

Movies::DataList::ListOfStrings Movies::DataList::listOfKinds() const
{
	return listOfStrings(&Data::kind);
}

Movies::DataList::SublistsByStrings Movies::DataList::moviesByGenres() const
{
	return sublistsByStrings(&Data::genres);
}

Movies::DataList::ListOfStrings Movies::DataList::listOfGenres() const
{
	return listOfStrings(&Data::genres);
}

Movies::DataList::SublistsByStrings Movies::DataList::moviesByCountries() const
{
	return sublistsByStrings(&Data::countries);
}

Movies::DataList::ListOfStrings Movies::DataList::listOfCountries() const
{
	return listOfStrings(&Data::countries);
}

Movies::DataList::SublistsByStrings Movies::DataList::moviesByDirectors() const
{
	return sublistsByStrings(&Data::directors);
}

Movies::DataList::ListOfStrings Movies::DataList::listOfDirectors() const
{
	return listOfStrings(&Data::directors);
}

Movies::DataList::SublistsByStrings Movies::DataList::moviesByWriters() const
{
	return sublistsByStrings(&Data::writers);
}

Movies::DataList::ListOfStrings Movies::DataList::listOfWriters() const
{
	return listOfStrings(&Data::writers);
}

Movies::DataList::SublistsByStrings Movies::DataList::moviesByActors() const
{
	return sublistsByStrings(&Data::actors);
}

Movies::DataList::ListOfStrings Movies::DataList::listOfActors() const
{
	return listOfStrings(&Data::actors);
}

Movies::DataList::SublistsByStrings Movies::DataList::moviesByYears(uint32_t step) const
{
	return sublistsByEpochStrings(&Data::year, step);
}

Movies::DataList::NumbersByStrings Movies::DataList::numbersByYears(uint32_t step,
		RangeTypes range_type, uint32_t required_min, uint32_t required_max) const
{
	return numbersInRange(step, range_type, required_min, required_max,
			[](const Data& data) { return data.year(); },
			[](uint32_t val, uint32_t step) { return Helper::epochString(val, step); });
}

Movies::DataList::SublistsByIntegers Movies::DataList::moviesByRatings() const
{
	return sublistsByIntegers(&Data::rating);
}

Movies::DataList::NumbersByIntegers Movies::DataList::numbersByRatings() const
{
	return numbersByIntegers(&Data::rating);
}

Movies::DataList::NumbersByIntegers Movies::DataList::numbersByViewDates() const
{
	return numbersByIntegers(&Data::viewYear);
}
