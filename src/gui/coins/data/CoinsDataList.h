#pragma once

#include "CoinsData.h"

#include <gui/base/data/BaseDataList.h>

namespace Coins
{

class DataList : public Base::DataList<Data>
{
public:
	DataList() = default;

	struct Summary
	{
		uint32_t coins_num = 0;
		uint32_t countries_num = 0;
		uint32_t min_year = Global::undefined_value;
		uint32_t max_year = Global::undefined_value;
		uint32_t min_diameter = Global::undefined_value; // step 0.1 mm
		uint32_t max_diameter = Global::undefined_value; // step 0.1 mm
		std::unordered_set<QString> list_of_countries;
	};
	Summary summary(const Synonyms& synonyms) const;

	Sublists2ByStrings coinsByCountries(const Synonyms& synonyms) const;
	NumbersByStringsVec numbersByCountries(size_t max_num, const Synonyms& synonyms) const;
	ListOfStrings listOfCountries() const;

	ListOfStrings listOfPeriods(const QString& country) const;

	Sublists3ByStrings coinsByRegions(const Synonyms& synonyms) const;
	NumbersByStringsVec numbersByRegions(size_t max_num, const Synonyms& synonyms) const;

	ListOfStrings listOfValues(const QString& country, const QString& period) const;

	ListOfStrings listOfCurrencies(const QString& country, const QString& period) const;

	ListOfStrings listOfStates() const;

	SublistsByStrings coinsByYears(uint32_t step = 1) const;
	NumbersByStrings numbersByYears(uint32_t step = 1,
			RangeTypes range_type = RangeTypes::Discrete,
			uint32_t required_min = 0, uint32_t required_max = 0) const;

	NumbersByStrings numbersByDiameters() const;
};

} // namespace Coins
