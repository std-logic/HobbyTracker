#include "Storage.h"
#include "csv/CsvStorage.h"

Csv::Data Storage::readCsv(const Csv::Settings& csv_settings)
{
	Csv::Storage::createFile(csv_settings);
	return Csv::Storage::readFile(csv_settings);
}

void Storage::writeCsv(const Csv::Settings& csv_settings, const Csv::Data& csv_data)
{
	Csv::Storage::createFile(csv_settings);
	Csv::Storage::writeFile(csv_settings, csv_data);
}
