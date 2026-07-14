#pragma once

namespace Music
{

enum class States
{
	Active,
	Inactive,
};

enum class DataListViewModes
{
	Simple,
	ByGenres,
	ByCountries,
	ByDecades,
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
