#pragma once

#include "BooksData.h"

#include <gui/base/data/BaseDataList.h>

#include <unordered_map>

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

	static auto sublistMinMaxYears(const SubListContainer& sublist)
	{
		std::pair<uint32_t, uint32_t> res(Global::undefined_value, Global::undefined_value);
		for (auto book : sublist) {
			res.first = Helper::checkMinYear(res.first, book->year());
			res.second = Helper::checkMaxYear(res.second, book->year());
		}
		return res;
	}
};

} // namespace Books
