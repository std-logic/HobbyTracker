#pragma once

#include "BooksData.h"

#include <gui/base/data/BaseDataList.h>

#include <map>

namespace Books
{

class DataList : public Base::DataList<Data>
{
public:
	DataList() = default;

	using ListByAuthors = std::map<QString, std::vector<const Data*>>;
	ListByAuthors listByAuthors() const
	{
		ListByAuthors list;
		for (const auto& book : _data_list) {
			list[book.author()].push_back(&book);
		}
		return list;
	}

	using ListByGenres = std::map<QString, std::vector<const Data*>>;
	ListByGenres listByGenres() const
	{
		ListByGenres list;
		for (const auto& book : _data_list) {
			list[book.genre()].push_back(&book);
		}
		return list;
	}
};

} // namespace Books
