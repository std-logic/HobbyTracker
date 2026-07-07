#include "BooksDataList.h"

#include <unordered_set>

Books::DataList::Summary Books::DataList::summary() const
{
	Summary sum;
	std::unordered_set<QString> list_authors, list_genres;
	for (const auto& data : _data_list) {
		list_authors.insert(data.author());
		list_genres.insert(data.genre());
		Helper::checkMinMax(data.year(), &sum.min_year, &sum.max_year);
		sum.rating += data.rating();
	}
	sum.authors_num = list_authors.size();
	sum.books_num = _data_list.size();
	sum.genres_num = list_genres.size();
	if (sum.books_num) { sum.rating /= sum.books_num; }
	return sum;
}

Books::DataList::SublistsByStrings Books::DataList::booksByAuthors() const
{
	return sublistsByStrings(&Data::author);
}

Books::DataList::ListOfStrings Books::DataList::listOfAuthorsTr() const
{
	return listOfStrings(&Data::authorTr);
}

Books::DataList::ListOfStrings Books::DataList::listOfAuthorsOrig() const
{
	return listOfStrings(&Data::authorOrig);
}

QString Books::DataList::findAuthorOrigByTr(const QString& author_tr) const
{
	for (const auto& data : _data_list) {
		if (author_tr == data.authorTr()) {
			return data.authorOrig();
		}
	}
	return QString();
}

Books::DataList::SublistsByStrings Books::DataList::booksByGenres() const
{
	return sublistsByStrings(&Data::genre);
}

Books::DataList::ListOfStrings Books::DataList::listOfGenres() const
{
	return listOfStrings(&Data::genre);
}

Books::DataList::SublistsByStrings Books::DataList::booksByYears(uint32_t step) const
{
	return sublistsByEpochStrings(&Data::year, step);
}

Books::DataList::NumbersByStrings Books::DataList::numbersByYears(uint32_t step,
		RangeTypes range_type, uint32_t required_min, uint32_t required_max) const
{
	return numbersInRange(step, range_type, required_min, required_max,
			[](const Data& data) { return data.year(); },
			[](uint32_t val, uint32_t step) { return Helper::epochString(val, step); });
}

Books::DataList::SublistsByIntegers Books::DataList::booksByRatings() const
{
	return sublistsByIntegers(&Data::rating);
}

Books::DataList::NumbersByIntegers Books::DataList::numbersByRatings() const
{
	return numbersByIntegers(&Data::rating);
}
