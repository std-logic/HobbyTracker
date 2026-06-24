#pragma once

#include <QString>
#include <QStringList>

#include <vector>

namespace Csv
{

class Data : public std::vector<QStringList>
{
public:
	Data() = default;
};

} // namespace Csv
