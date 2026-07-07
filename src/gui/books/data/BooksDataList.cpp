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
	SublistsByStrings list;
	for (const auto& data : _data_list) {
		list[data.author()].push_back(&data);
	}
	return list;
}

Books::DataList::ListOfStrings Books::DataList::listOfAuthorsTr() const
{
	ListOfStrings list;
	for (const auto& data : _data_list) {
		list.insert(data.authorTr());
	}
	return list;
}

Books::DataList::ListOfStrings Books::DataList::listOfAuthorsOrig() const
{
	ListOfStrings list;
	for (const auto& data : _data_list) {
		list.insert(data.authorOrig());
	}
	return list;
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
	SublistsByStrings list;
	for (const auto& data : _data_list) {
		list[data.genre()].push_back(&data);
	}
	return list;
}

Books::DataList::ListOfStrings Books::DataList::listOfGenres() const
{
	ListOfStrings list;
	for (const auto& data : _data_list) {
		list.insert(data.genre());
	}
	return list;
}

Books::DataList::SublistsByStrings Books::DataList::booksByYears(uint32_t step) const
{
	SublistsByStrings list;
	for (const auto& data : _data_list) {
		list[Helper::epochString(data.year(), step)].push_back(&data);
	}
	return list;
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
	SublistsByIntegers list;
	for (const auto& data : _data_list) {
		list[data.rating()].push_back(&data);
	}
	return list;
}

Books::DataList::NumbersByIntegers Books::DataList::numbersByRatings() const
{
	NumbersByIntegers list;
	for (const auto& data : _data_list) {
		++list[data.rating()];
	}
	return list;
}
