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
		summary.min_year = Helper::checkMinYear(summary.min_year, data.year());
		summary.max_year = Helper::checkMaxYear(summary.max_year, data.year());
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
		RangeTypes range_type, uint32_t min) const
{
	NumberByYears list;
	uint32_t real_min = std::numeric_limits<uint32_t>::max(), real_max = 0;
	for (const auto& data : _data_list) {
		auto year = data.year();
		if (real_min > year) { real_min = year; }
		if (real_max < year) { real_max = year; }
		if (range_type == RangeTypes::LinearWithMin) {
			if (year < min) {
				++list[QStringLiteral("&lt;%1").arg(min)];
				continue;
			}
		}
		++list[Helper::epochString(year, step)];
	}
	if (range_type != RangeTypes::Discrete) {
		if (range_type == RangeTypes::LinearWithMin) { real_min = min; }
		real_min = (real_min / step) * step;
		real_max = (real_max / step) * step;
		for (uint32_t year = real_min; year < real_max; year += step) {
			list.try_emplace(Helper::epochString(year, step), 0);
		}
	}
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
		res.first = Helper::checkMinYear(res.first, data->year());
		res.second = Helper::checkMaxYear(res.second, data->year());
	}
	return res;
}
