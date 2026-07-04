#pragma once

#include <QStringList>
#include <QCoreApplication>

namespace Csv
{
class Data;
}

namespace Books
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
		CLMN_AUTHOR_TR,
		CLMN_AUTHOR_ORIG,
		CLMN_TITLE_TR,
		CLMN_TITLE_ORIG,
		CLMN_GENRE,
		CLMN_YEAR,
		CLMN_RATING,
		NUM_OF_COLUMNS
	};
};

} // namespace Books
