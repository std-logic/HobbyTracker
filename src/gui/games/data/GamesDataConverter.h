#pragma once

#include <QStringList>
#include <QCoreApplication>

namespace Csv
{
class Data;
}

namespace Games
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
		CLMN_SERIES,
		CLMN_TITLE,
		CLMN_GENRE,
		CLMN_DEVELOPER,
		CLMN_YEAR,
		CLMN_RATING,
		NUM_OF_COLUMNS
	};
};

} // namespace Games
