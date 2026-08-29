#pragma once

namespace Trekking
{

enum class DataListViewModes
{
	Simple,
	ByCountries,
	ByRegions,
	ByKinds,
};

enum class ChartViewModes
{
	ByYears,
	ByCountries,
	ByRegions,
};

enum CsvFiles
{
	CsvFileData,
	NumOfCsvFiles
};

inline const char* csv_file_names[NumOfCsvFiles] =
{
	"hobby_trekking_data.csv",
};

inline const char settings_group_name[] = "trekking";

} // namespace Trekking
