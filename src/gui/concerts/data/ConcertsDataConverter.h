#pragma once

#include <QStringList>
#include <QCoreApplication>

namespace Csv
{
class Data;
}

namespace Concerts
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
		CLMN_ARTISTS,
		CLMN_KINDS,
		CLMN_COUNTRY,
		CLMN_CITY,
		CLMN_PLACE,
		NUM_OF_COLUMNS
	};
};

} // namespace Concerts
