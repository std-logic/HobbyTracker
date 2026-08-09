#pragma once

#include <QStringList>
#include <QCoreApplication>

namespace Csv
{
class Data;
}

namespace Coins
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
		CLMN_COUNTRY,
		CLMN_PERIOD,
		CLMN_VALUE,
		CLMN_YEAR,
		CLMN_VERSION,
		CLMN_CURRENCY,
		CLMN_TITLE,
		CLMN_DIAMETER,
		CLMN_STATE,
		CLMN_PRICE,
		CLMN_NUMBER,
		CLMN_LABEL,
		CLMN_COMMENT,
		NUM_OF_COLUMNS
	};
};

} // namespace Coins
