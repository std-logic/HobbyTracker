#pragma once

#include <cstddef>

namespace Csv
{
class Data;
class Settings;
}

class Storage
{
public:
	Storage() = delete;

	static Csv::Data readCsv(size_t index, const Csv::Settings& csv_settings);
	static bool writeCsv(size_t index, const Csv::Settings& csv_settings, const Csv::Data& csv_data);
};
