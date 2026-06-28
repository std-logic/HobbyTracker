#pragma once

namespace Csv
{
class Data;
class Settings;
}

class Storage
{
public:
	Storage() = delete;

	static Csv::Data readCsv(const Csv::Settings& csv_settings);
	static void writeCsv(const Csv::Settings& csv_settings, const Csv::Data& csv_data);
};
