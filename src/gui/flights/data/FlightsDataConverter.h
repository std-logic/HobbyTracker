#pragma once

#include "../common/FlightsCommon.h"

#include <QStringList>
#include <QCoreApplication>

namespace Csv
{
class Data;
}

namespace Flights
{

class DataList;

class DataConverter
{
	Q_DECLARE_TR_FUNCTIONS(DataConverter)
public:
	DataConverter() = delete;

	static QStringList getDefaultCsvHeader();

	static DataList conv(const Csv::Data& csv_data);
	static Csv::Data conv(const DataList& data_list);

private:
	enum Columns
	{
		CLMN_DATE,
		CLMN_POINT_FIRST,
		CLMN_POINT_LAST = CLMN_POINT_FIRST + max_points_num - 1,
		NUM_OF_COLUMNS
	};
};

} // namespace Flights
