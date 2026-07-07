#pragma once

#include "BooksData.h"

#include <gui/base/data/BaseDataList.h>

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

	SublistsByStrings booksByAuthors() const;
	ListOfStrings listOfAuthorsTr() const;
	ListOfStrings listOfAuthorsOrig() const;
	QString findAuthorOrigByTr(const QString& author_tr) const;

	SublistsByStrings booksByGenres() const;
	ListOfStrings listOfGenres() const;

	SublistsByStrings booksByYears(uint32_t step = 1) const;
	NumbersByStrings numbersByYears(uint32_t step = 1,
			RangeTypes range_type = RangeTypes::Discrete,
			uint32_t required_min = 0, uint32_t required_max = 0) const;

	SublistsByIntegers booksByRatings() const;
	NumbersByIntegers numbersByRatings() const;
};

} // namespace Books
