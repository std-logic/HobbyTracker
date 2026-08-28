#include "Regions.h"

#include <storage/Storage.h>
#include <storage/csv/CsvData.h>
#include <storage/csv/CsvSettings.h>

void Regions::init()
{
	Csv::Settings csv_settings;
	csv_settings.setFileName(0, ":/data/regions.csv");
	auto csv_data = Storage::readCsv(0, csv_settings);

	for (const auto& line : csv_data) {
		int line_size = line.size();
		if (CLMN_REGIONS < line_size) {
			_country_to_region[line[CLMN_COUNTRY]] = line[CLMN_REGIONS];
		}
	}
}

QString Regions::get(const QString& country)
{
	return	_country_to_region.contains(country) ?
			_country_to_region[country] :
			QStringLiteral("Неизвестный");
}

QStringList Regions::get(const QStringList& countries)
{
	QStringList regions;
	for (const auto& country : countries) {
		auto region = get(country);
		if (!regions.contains(region)) {
			regions.append(region);
		}
	}
	return regions;
}
