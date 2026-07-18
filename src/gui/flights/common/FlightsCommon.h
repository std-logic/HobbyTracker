#pragma once

#include <cstddef>

namespace Flights
{

constexpr size_t max_points_num = 5;

enum class DataListViewModes
{
	ByYears,
	ByCountries,
	ByCities,
	ByAirports,
	ByRoutes,
	AirportsTree,
	Simple,
};

enum CsvFiles
{
	CsvFileData,
	NumOfCsvFiles
};

inline const char* csv_file_names[NumOfCsvFiles] =
{
	"hobby_flights_data.csv"
};

inline const char settings_group_name[] = "flights";

} // namespace Flights
