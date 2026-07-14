#pragma once

#include <gui/base/data/BaseSettings.h>
#include <storage/csv/CsvSettings.h>

namespace Music
{

class Settings : public Base::Settings
{
public:
	Settings();

	void checkFirstRun() override;
	void save() const override;
	void load() override;

	inline void setCsvSettings(const Csv::Settings& csv_settings)
	{ _csv_settings = csv_settings; }
	inline Csv::Settings csvSettings() const
	{ return _csv_settings; }

private:
	Csv::Settings _csv_settings;
};

} // namespace Music
