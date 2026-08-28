#include "MoviesDataList.h"

#include <common/Regions.h>

#include <unordered_set>
#include <unordered_map>

Movies::DataList::Summary Movies::DataList::summary(bool favorites_only) const
{
	Summary sum;
	std::unordered_set<QString> list_of_countries;
	for (const auto& data : _data_list) {
		if (favorites_only && !data.isFavorite()) { continue; }
		++sum.viewed_num;
		if (data.kind() == QStringLiteral("Фильм")) { ++sum.movies_num; }
		if (data.kind() == QStringLiteral("Сериал")) { ++sum.series_num; }
		if (data.kind() == QStringLiteral("Мультфильм")) { ++sum.animation_num; }
		if (data.kind() == QStringLiteral("Мультсериал")) { ++sum.animation_series_num; }
		auto countries = data.countries();
		for (const auto& country : countries) { list_of_countries.insert(country); }
		Helper::checkMinMax(data.yearStart(), &sum.min_year, &sum.max_year);
		sum.rating += data.rating();
	}
	sum.countries_num = list_of_countries.size();
	if (sum.viewed_num) { sum.rating /= sum.viewed_num; }
	return sum;
}

void Movies::DataList::setFavorites(const DataList& favorites_list)
{
	std::unordered_map<QString, const Data*> favorites_map;
	for (const auto& favorites_data : favorites_list) {
		favorites_map[favorites_data.id()] = &favorites_data;
	}

	for (auto& data : _data_list) {
		if (favorites_map.contains(data.id())) {
			auto favorites_data = favorites_map[data.id()];
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

Movies::DataList Movies::DataList::getFavorites() const
{
	DataList favorites_list;
	for (const auto& data : _data_list) {
		if (data.isFavorite()) {
			favorites_list.add(data);
		}
	}
	std::ranges::sort(favorites_list, {}, &Data::titleTr);
	return favorites_list;
}

Movies::DataList::SublistsByStrings Movies::DataList::moviesByKinds(bool favorites_only) const
{
	return sublistsByStrings(&Data::kind, &Data::isFavorite, favorites_only);
}

Movies::DataList::ListOfStrings Movies::DataList::listOfKinds() const
{
	return listOfStrings(&Data::kind);
}

Movies::DataList::SublistsByStrings Movies::DataList::moviesByGenres(bool favorites_only) const
{
	return sublistsByStrings(&Data::genres, &Data::isFavorite, favorites_only);
}

Movies::DataList::NumbersByStringsVec Movies::DataList::numbersByGenres(
		size_t max_num, bool favorites_only) const
{
	return sortedVec(numbersByStrings(&Data::genres, &Data::isFavorite, favorites_only), max_num);
}

Movies::DataList::ListOfStrings Movies::DataList::listOfGenres() const
{
	return listOfStrings(&Data::genres);
}

Movies::DataList::SublistsByStrings Movies::DataList::moviesByCountries(
		const Synonyms& synonyms, bool favorites_only) const
{
	return sublistsByStrings(&Data::countries, synonyms, &Data::isFavorite, favorites_only);
}

Movies::DataList::NumbersByStringsVec Movies::DataList::numbersByCountries(
		size_t max_num, const Synonyms& synonyms, bool favorites_only) const
{
	return sortedVec(numbersByStrings(&Data::countries, synonyms, &Data::isFavorite, favorites_only), max_num);
}

Movies::DataList::ListOfStrings Movies::DataList::listOfCountries() const
{
	return listOfStrings(&Data::countries);
}

Movies::DataList::Sublists2ByStrings Movies::DataList::moviesByRegions(
		const Synonyms& synonyms, bool favorites_only) const
{
	Sublists2ByStrings list;
	for (const auto& data : _data_list) {
		if (favorites_only && !data.isFavorite()) { continue; }
		auto countries = data.countries();
		std::set<QString> unique_countries;
		for (const auto& country : countries) {
			auto synonym_for_country = synonyms.contains(country) ? synonyms.at(country) : country;
			if (!unique_countries.contains(synonym_for_country)) {
				unique_countries.insert(synonym_for_country);
				auto region = Regions::get(synonym_for_country);
				list[region][synonym_for_country].push_back(&data);
			}
		}
	}
	return list;
}

Movies::DataList::NumbersByStringsVec Movies::DataList::numbersByRegions(
		size_t max_num, const Synonyms& synonyms, bool favorites_only) const
{
	NumbersByStrings list;
	for (const auto& data : _data_list) {
		if (favorites_only && !data.isFavorite()) { continue; }
		auto countries = data.countries();
		std::set<QString> unique_regions;
		for (const auto& country : countries) {
			auto synonym_for_country = synonyms.contains(country) ? synonyms.at(country) : country;
			auto region = Regions::get(synonym_for_country);
			if (!unique_regions.contains(region)) {
				unique_regions.insert(region);
				++list[region];
			}
		}
	}
	return sortedVec(list, max_num);
}

Movies::DataList::SublistsByStrings Movies::DataList::moviesByDirectors(bool favorites_only) const
{
	return sublistsByStrings(&Data::directors, &Data::isFavorite, favorites_only);
}

Movies::DataList::NumbersByStringsVec Movies::DataList::numbersByDirectors(
		size_t max_num, bool favorites_only) const
{
	return sortedVec(numbersByStrings(&Data::directors, &Data::isFavorite, favorites_only), max_num);
}

Movies::DataList::ListOfStrings Movies::DataList::listOfDirectors() const
{
	return listOfStrings(&Data::directors);
}

Movies::DataList::SublistsByStrings Movies::DataList::moviesByWriters(bool favorites_only) const
{
	return sublistsByStrings(&Data::writers, &Data::isFavorite, favorites_only);
}

Movies::DataList::NumbersByStringsVec Movies::DataList::numbersByWriters(
		size_t max_num, bool favorites_only) const
{
	return sortedVec(numbersByStrings(&Data::writers, &Data::isFavorite, favorites_only), max_num);
}

Movies::DataList::ListOfStrings Movies::DataList::listOfWriters() const
{
	return listOfStrings(&Data::writers);
}

Movies::DataList::SublistsByStrings Movies::DataList::moviesByActors(bool favorites_only) const
{
	return sublistsByStrings(&Data::actors, &Data::isFavorite, favorites_only);
}

Movies::DataList::NumbersByStringsVec Movies::DataList::numbersByActors(
		size_t max_num, bool favorites_only) const
{
	return sortedVec(numbersByStrings(&Data::actors, &Data::isFavorite, favorites_only), max_num);
}

Movies::DataList::ListOfStrings Movies::DataList::listOfActors() const
{
	return listOfStrings(&Data::actors);
}

Movies::DataList::SublistsByStrings Movies::DataList::moviesByYears(uint32_t step, bool favorites_only) const
{
	return sublistsByEpochStrings(&Data::yearStart, step, &Data::isFavorite, favorites_only);
}

Movies::DataList::NumbersByStrings Movies::DataList::numbersByYears(uint32_t step,
		RangeTypes range_type, uint32_t required_min, uint32_t required_max,
		bool favorites_only) const
{
	return numbersInRange(step, range_type, required_min, required_max,
			[](const Data& data) { return data.yearStart(); },
			[](const Data&)->int { return 1; },
			[](uint32_t val, uint32_t step) { return Helper::epochString(val, step); },
			[favorites_only](const Data& data)->bool { return !favorites_only || data.isFavorite(); }
	);
}

Movies::DataList::SublistsByIntegers Movies::DataList::moviesByRatings(bool favorites_only) const
{
	return sublistsByIntegers(&Data::rating, &Data::isFavorite, favorites_only);
}

Movies::DataList::NumbersByIntegers Movies::DataList::numbersByRatings(bool favorites_only) const
{
	return numbersByIntegers(&Data::rating, &Data::isFavorite, favorites_only);
}

Movies::DataList::NumbersByIntegers Movies::DataList::numbersByViewDates(bool favorites_only) const
{
	return numbersByIntegers(&Data::viewYear, &Data::isFavorite, favorites_only);
}
