#include "CoinsDataList.h"

#include <unordered_set>

Coins::DataList::Summary Coins::DataList::summary() const
{
	Summary sum;
	std::unordered_set<QString> list_of_countries;
	for (const auto& data : _data_list) {
		list_of_countries.insert(data.country());
		Helper::checkMinMax(data.year(), &sum.min_year, &sum.max_year);
		Helper::checkMinMax(qRound(data.diameter().toDouble()*10),
							&sum.min_diameter, &sum.max_diameter);
	}
	sum.countries_num = list_of_countries.size();
	sum.coins_num = _data_list.size();
	return sum;
}

Coins::DataList::SublistsByStrings Coins::DataList::coinsByCountries(
		const Synonyms& synonyms) const
{
	SublistsByStrings list;
	for (const auto& data : _data_list) {
		auto country = data.country();
		auto key = synonyms.contains(country) ? synonyms.at(country) : country;
		list[key].push_back(&data);
	}
	return list;
}

Coins::DataList::ListOfStrings Coins::DataList::listOfCountries() const
{
	return listOfStrings(&Data::country);
}

Coins::DataList::SublistsByStrings Coins::DataList::coinsByPeriods(
		const Synonyms& synonyms) const
{
	SublistsByStrings list;
	for (const auto& data : _data_list) {
		auto country = data.country();
		auto key = synonyms.contains(country) ?
				data.countryPeriod(synonyms.at(country)) :
				data.countryPeriod();
		list[key].push_back(&data);
	}
	return list;
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

Coins::DataList::ListOfStrings Coins::DataList::listOfPeriods(
		const QString& country, const Synonyms& synonyms) const
{
	ListOfStrings list;
	for (const auto& data : _data_list) {
		if (synonyms.contains(data.country())) {
			if (synonyms.at(data.country()) == country) {
				list.insert(data.period());
			}
		} else if (data.country() == country) {
			list.insert(data.period());
		}
	}
	return list;
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
