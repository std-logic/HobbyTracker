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
			}
			if (CLMN_FORMER < line_size) {
				data.is_former = (line[CLMN_FORMER] == "+");
			}
			if (CLMN_UNION < line_size) {
				data.is_union = (line[CLMN_UNION] == "+");
			}
			if (CLMN_COMMENT < line_size) {
				data.comment = line[CLMN_COMMENT];
			}

			_country_data[country] = data;
			if (!data.region.isEmpty() && !data.is_former && !data.is_union) {
				_region_countries[data.region].insert(country);
				++_countries_total_num;
			}
		}
	}
}

QString Regions::region(const QString& country)
{
	return	_country_data.contains(country) ?
			_country_data[country].region :
			QStringLiteral("Неизвестный");
}

QStringList Regions::region(const QStringList& countries)
{
	QStringList regions;
	for (const auto& country : countries) {
		auto reg = region(country);
		if (!regions.contains(reg)) {
			regions.append(reg);
		}
	}
	return regions;
}

QString Regions::comment(const QString& country)
{
	return	_country_data.contains(country) ?
			_country_data[country].comment :
			QStringLiteral("");
}

bool Regions::isFormer(const QString& country)
{
	return	_country_data.contains(country) ?
			_country_data[country].is_former :
			false;
}

bool Regions::isUnion(const QString& country)
{
	return	_country_data.contains(country) ?
			_country_data[country].is_union :
			false;
}

QStringList Regions::missingCountries(const QString& region,
		const std::unordered_set<QString>& present_countries)
{
	QStringList out;
	const auto& region_countries = _region_countries[region];
	for (const auto& country : region_countries) {
		if (!present_countries.contains(country)) {
			out.append(country);
		}
	}
	return out;
}

QString Regions::progress(const QString& region,
		const std::unordered_set<QString>& present_countries)
{
	int present_num = present_countries.size(), former_num = 0, union_num = 0;
	for (const auto& country : present_countries) {
		const auto& data = _country_data[country];
		if (data.is_former || data.is_union) {
			--present_num;
			if (data.is_former) { ++former_num; }
			if (data.is_union) { ++union_num; }
		}
	}
	int total_region_num = _region_countries[region].size();
	double total_region_percent = 100. * present_num / total_region_num;

	QString out = tr("Всего стран:\n%1/%2 (%3%)")
			.arg(present_num)
			.arg(total_region_num)
			.arg(total_region_percent, 0, 'f', 0);

	if (former_num > 0) {
		out += tr("\n\nИсчезнувших стран:\n%1").arg(former_num);
	}

	if (union_num > 0) {
		out += tr("\n\nОбъединений стран:\n%1").arg(union_num);
	}

	auto missing_countries = missingCountries(region, present_countries);
	if (!missing_countries.isEmpty()) {
		out += tr("\n\nОстались:");
		int cnt = 0;
		for (const auto& country : missing_countries) {
			if (++cnt > 30) { out += "\n..."; break; }
			out += "\n" + country;
		}
	}

	return out;
}

QString Regions::progress(const std::unordered_set<QString>& present_countries)
{
	int present_num = present_countries.size(), former_num = 0, union_num = 0;
	std::unordered_map<QString, int> present_num_by_regions;
	for (const auto& country : present_countries) {
		const auto& data = _country_data[country];
		if (data.is_former || data.is_union) {
			--present_num;
			if (data.is_former) { ++former_num; }
			if (data.is_union) { ++union_num; }
		} else {
			++present_num_by_regions[data.region];
		}
	}
	double total_percent = 100. * present_num / _countries_total_num;

	QString out = tr("Всего стран:\n%1/%2 (%3%)")
			.arg(present_num)
			.arg(_countries_total_num)
			.arg(total_percent, 0, 'f', 0);

	for (const auto& [region, countries] : _region_countries) {
		int present_region_num = present_num_by_regions[region];
		if (present_region_num > 0) {
			int total_region_num = countries.size();
			double region_percent = 100. * present_region_num / total_region_num;
			out += tr("\n%1:\n%2/%3 (%4%)")
					.arg(region)
					.arg(present_region_num)
					.arg(total_region_num)
					.arg(region_percent, 0, 'f', 0);
		}
	}

	if (former_num > 0) {
		out += tr("\n\nИсчезнувших стран:\n%1").arg(former_num);
	}

	if (union_num > 0) {
		out += tr("\n\nОбъединений стран:\n%1").arg(union_num);
	}

	return out;
}
