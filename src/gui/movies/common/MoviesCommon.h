#pragma once

namespace Movies
{

enum class DataListViewModes
{
	Simple,
	ByDirectors,
	ByWriters,
	ByActors,
	ByGenres,
	ByCountries,
	ByYears,
	ByDecades,
	ByRatings,
};

enum class ChartViewModes
{
	ByYears,
	ByDecades,
	ByRatings,
	ByViewDates,
};

enum CsvFiles
{
	CsvFileData,
	CsvFileFavorites,
	CsvFileExtra,
	NumOfCsvFiles
};

inline const char* csv_file_names[NumOfCsvFiles] =
{
	"hobby_movies_data.csv",
	"hobby_movies_favorites.csv",
	"hobby_movies_extra.csv"
};

inline const char settings_group_name[] = "movies";

} // namespace Movies
