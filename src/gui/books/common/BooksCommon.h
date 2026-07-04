#pragma once

namespace Books
{

enum class DataListViewModes
{
	ByAuthors,
	ByGenres,
	ByDecades,
	ByCenturies,
	ByRatings,
	Simple,
};

enum class ChartViewModes
{
	ByDecades,
	ByCenturies,
	ByRatings,
};

enum CsvFiles
{
	CsvFileData,
	CsvFileExtra,
	NumOfCsvFiles
};

inline const char* csv_file_names[NumOfCsvFiles] =
{
	"hobby_books_data.csv",
	"hobby_books_extra.csv"
};

inline const char settings_group_name[] = "books";

} // namespace Books
