#pragma once

#include <gui/base/data/BaseSettings.h>

namespace Player
{

class Settings : public Base::Settings
{
public:
	Settings();

	void checkFirstRun() override;
	void save() const override;
	void load() override;

	template<typename T>
	inline void setDefaultDir(T&& default_dir)
	{ _default_dir = std::forward<T>(default_dir); }
	inline QString defaultDir() const
	{ return _default_dir; }

private:
	QString _default_dir;
};

} // namespace Player
