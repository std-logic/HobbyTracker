#pragma once

namespace Coins
{

enum class DataListViewModes
{
	ByCountries,
	ByDecades,
	ByCenturies,
	Simple,
};

enum class ChartViewModes
{
	ByCountries,
	ByDecades,
	ByCenturies,
	ByDiameters,
};

enum CsvFiles
{
	CsvFileData,
	CsvFileExtra,
	NumOfCsvFiles
};

inline const char* csv_file_names[NumOfCsvFiles] =
{
	"hobby_coins_data.csv",
	"hobby_coins_extra.csv"
};

inline const char settings_group_name[] = "coins";

} // namespace Coins
