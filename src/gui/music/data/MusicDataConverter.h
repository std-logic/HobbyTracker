#pragma once

#include <QStringList>
#include <QCoreApplication>

namespace Csv
{
class Data;
}

namespace Music
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
		CLMN_TITLE,
		CLMN_GENRE,
		CLMN_COUNTRY,
		CLMN_YEAR,
		CLMN_STATE,
		NUM_OF_COLUMNS
	};
};

} // namespace Music
