#pragma once

namespace Bike
{

enum class DataListViewModes
{
	Simple,
	ByCountries,
};

enum class ChartViewModes
{
	ByTrips,
	ByCountries,
	ByDist,
	ByTime,
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
