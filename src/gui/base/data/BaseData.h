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

	bool operator==(const Data& other) const noexcept = default;
};

} // namespace Base
