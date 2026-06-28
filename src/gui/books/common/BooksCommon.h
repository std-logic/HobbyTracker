#pragma once

namespace Books
{

enum class ListViewModes
{
	ByAuthors,
	ByGenres,
	ByDecades,
	ByCenturies,
	ByRatings,
	Simple,
};

inline const char data_file_name[] = "hobby_books_data.csv";
inline const char settings_group_name[] = "books";

} // namespace Books
