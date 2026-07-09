#pragma once

namespace Bike
{

enum class ChartViewModes
{
	ByDist,
	ByTime,
	ByTrips,
};

enum CsvFiles
{
	CsvFileData,
	CsvFileTrip,
	NumOfCsvFiles
};

inline const char* csv_file_names[NumOfCsvFiles] =
{
	"hobby_bike_data.csv",
	"hobby_bike_trip.csv",
};

inline const char settings_group_name[] = "bike";

} // namespace Bike
