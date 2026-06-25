#pragma once

#include <QString>

namespace Base
{

class Settings
{
public:
	Settings();

	virtual void save() const = 0;
	virtual void load() = 0;

protected:
	virtual QString fullPath(const QString& file_name) const;
};

} // namespace Base
