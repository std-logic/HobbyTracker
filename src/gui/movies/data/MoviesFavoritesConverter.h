#pragma once

#include <QStringList>
#include <QCoreApplication>

namespace Csv
{
class Data;
}

namespace Movies
{

class DataList;

class FavoritesConverter
{
	Q_DECLARE_TR_FUNCTIONS(FavoritesConverter)
public:
	FavoritesConverter() = delete;

	static QStringList getDefaultCsvHeader();

	static DataList conv(const Csv::Data& csv_data);
	static Csv::Data conv(const DataList& data_list);

private:
	enum Columns
	{
		CLMN_TITLE_TR,
		CLMN_TITLE_ORIG,
		CLMN_YEAR,
		CLMN_GENRES,
		CLMN_COUNTRIES,
		CLMN_DIRECTORS,
		CLMN_WRITERS,
		CLMN_ACTORS,
		NUM_OF_COLUMNS
	};
};

} // namespace Movies
