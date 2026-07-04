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
	Summary summary() const;

	using BooksByAuthors = std::unordered_map<QString, SubListContainer>;
	BooksByAuthors booksByAuthors() const;
	ListOfStrings listOfAuthorsTr() const;
	ListOfStrings listOfAuthorsOrig() const;
	QString findAuthorOrigByTr(const QString& author_tr) const;

	using BooksByGenres = std::unordered_map<QString, SubListContainer>;
	BooksByGenres booksByGenres() const;
	ListOfStrings listOfGenres() const;

	using BooksByYears = std::unordered_map<QString, SubListContainer>;
	BooksByYears booksByYears(uint32_t step = 1) const;
	NumbersInRange numbersByYears(uint32_t step = 1,
			RangeTypes range_type = RangeTypes::Discrete,
			uint32_t required_min = 0, uint32_t required_max = 0) const;

	using BooksByRatings = std::unordered_map<uint32_t, SubListContainer>;
	BooksByRatings booksByRatings() const;
	using NumbersByRatings = std::map<uint32_t, uint32_t>;
	NumbersByRatings numbersByRatings() const;

	static QString yearString(const SubListContainer& sublist);

	int findIndexById(const QString& id);
};

} // namespace Books
