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
		if (CLMN_COUNTRY < line_size) {
			QString country = line[CLMN_COUNTRY];
			CountryData data;
			if (CLMN_REGIONS < line_size) {
				data.region = line[CLMN_REGIONS];
				_region_countries[data.region].insert(country);
			}
			if (CLMN_FORMER < line_size) {
				data.is_former = (line[CLMN_FORMER] == "+");
			}
			if (CLMN_UNION < line_size) {
				data.is_union = (line[CLMN_UNION] == "+");
			}
			_country_data[country] = data;
		}
	}
}

QString Regions::get(const QString& country)
{
	return	_country_data.contains(country) ?
			_country_data[country].region :
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

QStringList Regions::missingCountries(const QString& region,
		const std::set<QString>& present_countries)
{
	QStringList out;
	const auto& region_countries = _region_countries[region];
	for (const auto& country : region_countries) {
		const auto& data = _country_data[country];
		if (data.is_former || data.is_union) { continue; }
		if (present_countries.contains(country)) { continue; }
		out.append(country);
	}
	return out;
}

QString Regions::progress(const QString& region,
		const std::set<QString>& present_countries)
{
	int present_num = present_countries.size(), former_num = 0, union_num = 0;
	for (const auto& country : present_countries) {
		const auto& data = _country_data[country];
		if (data.is_former) { --present_num; ++former_num; }
		if (data.is_union) { --present_num; ++union_num; }
	}
	auto missing_countries = missingCountries(region, present_countries);
	int missing_num = missing_countries.size();
	int total_num = present_num + missing_num;
	double percent = 100. * static_cast<double>(present_num) / static_cast<double>(total_num);

	QString out = tr("Прогресс по странам:\n%1/%2 (%3%)")
			.arg(present_num).arg(total_num).arg(percent, 0, 'f', 0);

	if (former_num > 0) {
		out += tr("\n\nИсчезнувших стран:\n%1").arg(former_num);
	}

	if (union_num > 0) {
		out += tr("\n\nСоюзов стран:\n%1").arg(union_num);
	}

	if (missing_num > 0) {
		out += tr("\n\nОстались:");
		int cnt = 0;
		for (const auto& country : missing_countries) {
			if (++cnt > 40) { out += "\n..."; break; }
			out += "\n" + country;
		}
	}

	return out;
}
