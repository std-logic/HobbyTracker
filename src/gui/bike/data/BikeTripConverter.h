#pragma once

#include <QStringList>
#include <QCoreApplication>

namespace Csv
{
class Data;
}

namespace Bike
{

class TripList;

class TripConverter
{
	Q_DECLARE_TR_FUNCTIONS(TripConverter)
public:
	TripConverter() = delete;

	static QStringList getDefaultCsvHeader();

	static TripList conv(const Csv::Data& csv_data);
	static Csv::Data conv(const TripList& data_list);

private:
	enum Columns
	{
		CLMN_DATE_START,
		CLMN_DATE_END,
		CLMN_DIST,
		CLMN_TIME,
		CLMN_COUNTRIES,
		CLMN_PLACES,
		NUM_OF_COLUMNS
	};
};

} // namespace Bike
