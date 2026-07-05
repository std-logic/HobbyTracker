#pragma once

namespace Games
{

enum class DataListViewModes
{
	BySeries,
	ByGenres,
	ByDevelopers,
	ByYears,
	ByDecades,
	ByRatings,
	Simple,
};

enum class ChartViewModes
{
	ByYears,
	ByDecades,
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
	"hobby_games_data.csv",
	"hobby_games_extra.csv"
};

inline const char settings_group_name[] = "games";

} // namespace Games
