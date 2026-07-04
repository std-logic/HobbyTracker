#include "Storage.h"
#include "csv/CsvStorage.h"

Csv::Data Storage::readCsv(size_t index, const Csv::Settings& csv_settings)
{
	Csv::Storage::createFile(index, csv_settings);
	return Csv::Storage::readFile(index, csv_settings);
}

bool Storage::writeCsv(size_t index, const Csv::Settings& csv_settings, const Csv::Data& csv_data)
{
	return Csv::Storage::writeFile(index, csv_settings, csv_data);
}
