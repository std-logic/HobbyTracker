#pragma once

#include <gui/base/data/BaseSettings.h>
#include <storage/csv/CsvSettings.h>

namespace Concerts
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

	template<typename T>
	inline void setPhotoDir(T&& photo_dir)
	{ _photo_dir = std::forward<T>(photo_dir); }
	inline QString photoDir() const
	{ return _photo_dir; }

private:
	Csv::Settings _csv_settings;
	QString _photo_dir;
};

} // namespace Concerts
