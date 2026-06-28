#pragma once

#include "BooksData.h"

#include <gui/base/data/BaseDataList.h>

#include <unordered_map>
#include <unordered_set>

namespace Books
{

class DataList : public Base::DataList<Data>
{
public:
	DataList() = default;

	using ListByAuthors = std::unordered_map<QString, SubListContainer>;
	ListByAuthors listByAuthors() const
	{
		ListByAuthors list;
		for (const auto& book : _data_list) {
			list[book.author()].push_back(&book);
		}
		return list;
	}

	using ListByGenres = std::unordered_map<QString, SubListContainer>;
	ListByGenres listByGenres() const
	{
		ListByGenres list;
		for (const auto& book : _data_list) {
			list[book.genre()].push_back(&book);
		}
		return list;
	}

	using ListByYears = std::unordered_map<QString, SubListContainer>;
	ListByYears listByYears(uint32_t step = 1) const
	{
		ListByYears list;
		for (const auto& book : _data_list) {
			if (step == 1) {
				list[book.yearString(QStringLiteral("[Неизвестный]"))].push_back(&book);
			} else {
				list[Helper::epochString(book.year(), step)].push_back(&book);
			}
		}
		return list;
	}

	using ListByRatings = std::unordered_map<uint32_t, SubListContainer>;
	ListByRatings listByRatings() const
	{
		ListByRatings list;
		for (const auto& book : _data_list) {
			list[book.rating()].push_back(&book);
		}
		return list;
	}

	static auto sublistMinMaxYears(const SubListContainer& sublist)
	{
		std::pair<uint32_t, uint32_t> res(Global::undefined_value, Global::undefined_value);
		for (auto book : sublist) {
			res.first = Helper::checkMinYear(res.first, book->year());
			res.second = Helper::checkMaxYear(res.second, book->year());
		}
		return res;
	}

	struct Summary
	{
		int authors_num = 0;
		int books_num = 0;
		int genres_num = 0;
		int min_year = Global::undefined_value;
		int max_year = Global::undefined_value;
		double rating = 0.;
	};
	Summary getSummary() const
	{
		Summary summary;
		std::unordered_set<QString> list_authors;
		std::unordered_set<QString> list_genres;
		for (const auto& book : _data_list) {
			list_authors.insert(book.author());
			list_genres.insert(book.genre());
			summary.min_year = Helper::checkMinYear(summary.min_year, book.year());
			summary.max_year = Helper::checkMaxYear(summary.max_year, book.year());
			summary.rating += book.rating();
		}
		summary.authors_num = list_authors.size();
		summary.books_num = _data_list.size();
		summary.genres_num = list_genres.size();
		if (summary.books_num) {
			summary.rating /= summary.books_num;
		}
		return summary;
	}
};

} // namespace Books
