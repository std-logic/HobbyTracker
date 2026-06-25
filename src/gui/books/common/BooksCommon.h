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

inline const char DATA_FILE_NAME[] = "hobby_books_data.csv";
inline const char SETTINGS_FILE_NAME[] = "hobby_books_settings.ini";

} // namespace Books
