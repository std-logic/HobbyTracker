#pragma once

#include <QStringList>
#include <QCoreApplication>

namespace Csv
{
class Data;
}

namespace Trekking
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
		CLMN_DATE_START,
		CLMN_DATE_END,
		CLMN_TIME,
		CLMN_DIST,
		CLMN_PEAK,
		CLMN_KIND,
		CLMN_COUNTRIES,
		CLMN_PLACES,
		NUM_OF_COLUMNS
	};
};

} // namespace Trekking
