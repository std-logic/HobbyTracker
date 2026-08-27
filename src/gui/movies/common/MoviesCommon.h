#pragma once

namespace Movies
{

enum class DataListViewModes
{
	Simple,
	ByKinds,
	ByGenres,
	ByCountries,
	ByRegions,
	ByYears,
	ByDecades,
	ByDirectors,
	ByWriters,
	ByActors,
	ByRatings,
};

enum class ChartViewModes
{
	ByViewDates,
	ByGenres,
	ByCountries,
	ByYears,
	ByDecades,
	ByDirectors,
	ByWriters,
	ByActors,
	ByRatings,
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
