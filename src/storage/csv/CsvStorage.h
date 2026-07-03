#pragma once

#include "CsvData.h"
#include "CsvSettings.h"

namespace Csv
{

class Storage
{
public:
	Storage() = delete;

	static void createFile(const Settings& csv_settings);
	static Data readFile(const Settings& csv_settings);
	static bool writeFile(const Settings& csv_settings, const Data& csv_data);
};

} // namespace Csv
