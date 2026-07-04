#pragma once

#include "CsvData.h"
#include "CsvSettings.h"

namespace Csv
{

class Storage
{
public:
	Storage() = delete;

	static void createFile(size_t index, const Settings& csv_settings);
	static Data readFile(size_t index, const Settings& csv_settings);
	static bool writeFile(size_t index, const Settings& csv_settings, const Data& csv_data);
};

} // namespace Csv
