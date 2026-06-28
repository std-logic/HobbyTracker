#pragma once

#include <QString>

namespace Base
{

class Settings
{
public:
	Settings(const QString& group_name);
	virtual ~Settings() = default;

	virtual void save() const = 0;
	virtual void load() = 0;

protected:
	QString _group_name;
};

} // namespace Base
