#pragma once

#include <QString>

namespace Base
{

class Data
{
public:
	Data() = default;
	virtual ~Data() = default;

	virtual QString id() const = 0;
};

} // namespace Base
