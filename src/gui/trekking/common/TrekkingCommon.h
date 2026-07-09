#pragma once

namespace Trekking
{

enum class DataListViewModes
{
	Simple,
	ByCountries,
	ByKinds,
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
