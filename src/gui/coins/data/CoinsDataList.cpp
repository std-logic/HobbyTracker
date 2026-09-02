#include "CoinsDataList.h"

#include <common/Regions.h>

Coins::DataList::Summary Coins::DataList::summary(const Synonyms& synonyms) const
{
	Summary sum;
	for (const auto& data : _data_list) {
		auto country = data.country();
		auto synonym_for_country = synonyms.contains(country) ? synonyms.at(country) : country;
		sum.list_of_countries.insert(synonym_for_country);
		Helper::checkMinMax(data.year(), &sum.min_year, &sum.max_year);
		Helper::checkMinMax(qRound(data.diameter().toDouble()*10),
							&sum.min_diameter, &sum.max_diameter);
	}
	sum.countries_num = sum.list_of_countries.size();
	sum.coins_num = _data_list.size();
	return sum;
}

Coins::DataList::Sublists2ByStrings Coins::DataList::coinsByCountries(
		const Synonyms& synonyms) const
{
	Sublists2ByStrings list;
	for (const auto& data : _data_list) {
		auto country = data.country();
		auto synonym_for_country = synonyms.contains(country) ? synonyms.at(country) : country;
		list[synonym_for_country][data.period()].push_back(&data);
	}
	return list;
}

Coins::DataList::NumbersByStringsVec Coins::DataList::numbersByCountries(
		size_t max_num, const Synonyms& synonyms) const
{
	return sortedVec(numbersByStrings(&Data::country, synonyms), max_num);
}

Coins::DataList::ListOfStrings Coins::DataList::listOfCountries() const
{
	return listOfStrings(&Data::country);
}

Coins::DataList::ListOfStrings Coins::DataList::listOfPeriods(
		const QString& country) const
{
	ListOfStrings list;
	for (const auto& data : _data_list) {
		if (data.country() == country) {
			list.insert(data.period());
		}
	}
	return list;
}

Coins::DataList::Sublists3ByStrings Coins::DataList::coinsByRegions(
		const Synonyms& synonyms) const
{
	Sublists3ByStrings list;
	for (const auto& data : _data_list) {
		auto country = data.country();
		auto synonym_for_country = synonyms.contains(country) ? synonyms.at(country) : country;
		auto region = Regions::region(synonym_for_country);
		list[region][synonym_for_country][data.period()].push_back(&data);
	}
	return list;
}

Coins::DataList::NumbersByStringsVec Coins::DataList::numbersByRegions(
		size_t max_num, const Synonyms& synonyms) const
{
	NumbersByStrings list;
	for (const auto& data : _data_list) {
		auto country = data.country();
		auto synonym_for_country = synonyms.contains(country) ? synonyms.at(country) : country;
		auto region = Regions::region(synonym_for_country);
		++list[region];
	}
	return sortedVec(list, max_num);
}

Coins::DataList::ListOfStrings Coins::DataList::listOfValues(
		const QString& country, const QString& period) const
{
	ListOfStrings list;
	for (const auto& data : _data_list) {
		if ((data.country() == country) && (data.period() == period)) {
			list.insert(data.value());
		}
	}
	return list;
}

Coins::DataList::ListOfStrings Coins::DataList::listOfCurrencies(
		const QString& country, const QString& period) const
{
	ListOfStrings list;
	for (const auto& data : _data_list) {
		if ((data.country() == country) && (data.period() == period)) {
			list.insert(data.currency());
		}
	}
	return list;
}

Coins::DataList::ListOfStrings Coins::DataList::listOfStates() const
{
	return listOfStrings(&Data::state);
}

Coins::DataList::SublistsByStrings Coins::DataList::coinsByYears(uint32_t step) const
{
	return sublistsByEpochStrings(&Data::year, step);
}

Coins::DataList::NumbersByStrings Coins::DataList::numbersByYears(uint32_t step,
		RangeTypes range_type, uint32_t required_min, uint32_t required_max) const
{
	return numbersInRange(step, range_type, required_min, required_max,
			[](const Data& data) { return data.year(); },
			[](uint32_t val, uint32_t step) { return Helper::epochString(val, step); });
}

Coins::DataList::NumbersByStrings Coins::DataList::numbersByDiameters() const
{
	return numbersInRange(1, RangeTypes::Linear, 0, 0,
			[](const Data& data) { return data.diameterRounded(); },
			[](uint32_t val, uint32_t /*step*/) { return QString::number(val); });
}
