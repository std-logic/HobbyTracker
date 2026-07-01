#pragma once

#include "BooksData.h"

#include <gui/base/data/BaseDataList.h>

#include <unordered_map>
#include <map>

namespace Books
{

class DataList : public Base::DataList<Data>
{
public:
	DataList() = default;

	struct Summary
	{
		int authors_num = 0;
		int books_num = 0;
		int genres_num = 0;
		uint32_t min_year = Global::undefined_value;
		uint32_t max_year = Global::undefined_value;
		double rating = 0.;
	};
	Summary getSummary() const;

	using BooksByAuthors = std::unordered_map<QString, SubListContainer>;
	BooksByAuthors booksByAuthors() const;

	using BooksByGenres = std::unordered_map<QString, SubListContainer>;
	BooksByGenres booksByGenres() const;

	using BooksByYears = std::unordered_map<QString, SubListContainer>;
	BooksByYears booksByYears(uint32_t step = 1) const;
	using NumberByYears = std::map<QString, uint32_t>;
	NumberByYears numberByYears(uint32_t step = 1,
			RangeTypes range_type = RangeTypes::Discrete,
			uint32_t required_min = 0, uint32_t required_max = 0) const;

	using BooksByRatings = std::unordered_map<uint32_t, SubListContainer>;
	BooksByRatings booksByRatings() const;
	using NumberByRatings = std::map<uint32_t, uint32_t>;
	NumberByRatings numberByRatings() const;

	using SublistMinMaxYears = std::pair<uint32_t, uint32_t>;
	static SublistMinMaxYears sublistMinMaxYears(const SubListContainer& sublist);
};

} // namespace Books
