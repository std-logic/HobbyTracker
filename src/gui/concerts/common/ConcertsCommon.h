#pragma once

namespace Concerts
{

enum class DataListViewModes
{
	ByYears,
	ByArtists,
	ByTags,
	ByCountries,
	ByCities,
	ByPlaces,
	PlacesTree,
	Simple,
};

enum class ChartViewModes
{
	ByYears,
	ByArtists,
	ByCountries,
	ByCities,
	ByPlaces,
};

enum CsvFiles
{
	CsvFileData,
	CsvFileExtra,
	NumOfCsvFiles
};

inline const char* csv_file_names[NumOfCsvFiles] =
{
	"hobby_concerts_data.csv",
	"hobby_concerts_extra.csv"
};

inline const char settings_group_name[] = "concerts";

} // namespace Concerts
