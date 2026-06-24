#include "Storage.h"
#include "csv/CsvStorage.h"

Storage::Storage(QObject* parent)
	: QObject{parent}
{
}

void Storage::readCsv(const Csv::Settings& csv_settings)
{
	Csv::Storage::createFile(csv_settings);
	auto csv_data = Csv::Storage::readFile(csv_settings);
	emit dataCsv(csv_settings, csv_data);
}

void Storage::writeCsv(const Csv::Settings& csv_settings, const Csv::Data& csv_data)
{
	Csv::Storage::createFile(csv_settings);
	Csv::Storage::writeFile(csv_settings, csv_data);
}
