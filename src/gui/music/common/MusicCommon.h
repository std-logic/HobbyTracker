#pragma once

namespace Music
{

enum class States
{
	Inactive,
	Active,
};

enum class Live
{
	Unvisited,
	Visited,
};

enum class DataListViewModes
{
	Simple,
	ByGenres,
	ByCountries,
	ByDecades,
	ByLive,
	ByStates,
};

enum CsvFiles
{
	CsvFileData,
	CsvFileExtra,
	NumOfCsvFiles
};

inline const char* csv_file_names[NumOfCsvFiles] =
{
	"hobby_music_data.csv",
	"hobby_music_extra.csv"
};

inline const char settings_group_name[] = "music";

} // namespace Music
