#pragma once

namespace Bike
{

enum class ChartViewModes
{
	ByDist,
	ByTime,
};

enum CsvFiles
{
	CsvFileData,
	NumOfCsvFiles
};

inline const char* csv_file_names[NumOfCsvFiles] =
{
	"hobby_bike_data.csv",
};

inline const char settings_group_name[] = "bike";

} // namespace Bike
