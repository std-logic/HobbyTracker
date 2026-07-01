#include "BooksDataList.h"

#include <unordered_set>

Books::DataList::Summary Books::DataList::getSummary() const
{
	Summary summary;
	std::unordered_set<QString> list_authors;
	std::unordered_set<QString> list_genres;
	for (const auto& data : _data_list) {
		list_authors.insert(data.author());
		list_genres.insert(data.genre());
		Helper::checkMinMax(data.year(), &summary.min_year, &summary.max_year);
		summary.rating += data.rating();
	}
	summary.authors_num = list_authors.size();
	summary.books_num = _data_list.size();
	summary.genres_num = list_genres.size();
	if (summary.books_num) {
		summary.rating /= summary.books_num;
	}
	return summary;
}

Books::DataList::BooksByAuthors Books::DataList::booksByAuthors() const
{
	BooksByAuthors list;
	for (const auto& data : _data_list) {
		list[data.author()].push_back(&data);
	}
	return list;
}

Books::DataList::BooksByGenres Books::DataList::booksByGenres() const
{
	BooksByGenres list;
	for (const auto& data : _data_list) {
		list[data.genre()].push_back(&data);
	}
	return list;
}

Books::DataList::BooksByYears Books::DataList::booksByYears(uint32_t step) const
{
	BooksByYears list;
	for (const auto& data : _data_list) {
		list[Helper::epochString(data.year(), step)].push_back(&data);
	}
	return list;
}

Books::DataList::NumberByYears Books::DataList::numberByYears(uint32_t step,
		RangeTypes range_type, uint32_t required_min, uint32_t required_max) const
{
	NumberByYears list;
	fillNumbersInRange(&list, step, range_type, required_min, required_max,
			[](const Data& data) { return data.year(); },
			[](uint32_t val, uint32_t step) { return Helper::epochString(val, step); });
	return list;
}

Books::DataList::BooksByRatings Books::DataList::booksByRatings() const
{
	BooksByRatings list;
	for (const auto& data : _data_list) {
		list[data.rating()].push_back(&data);
	}
	return list;
}

Books::DataList::NumberByRatings Books::DataList::numberByRatings() const
{
	NumberByRatings list;
	for (const auto& data : _data_list) {
		++list[data.rating()];
	}
	return list;
}

Books::DataList::SublistMinMaxYears Books::DataList::sublistMinMaxYears(const SubListContainer& sublist)
{
	SublistMinMaxYears res(Global::undefined_value, Global::undefined_value);
	for (auto data : sublist) {
		Helper::checkMinMax(data->year(), &res.first, &res.second);
	}
	return res;
}
