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
		CLMN_RATING,
		CLMN_BACKUP_ID,
		CLMN_VIEW_DATE,
		CLMN_TITLE_TR,
		CLMN_TITLE_ORIG,
		CLMN_KIND,
		CLMN_YEAR,
		CLMN_GENRES,
		CLMN_COUNTRIES,
		CLMN_TIME,
		CLMN_AGE_LIMIT,
		CLMN_MPAA,
		CLMN_BUDGET,
		CLMN_BOX_USA,
		CLMN_BOX_WORLD,
		CLMN_BOX_RU,
		CLMN_AUDIENCE,
		CLMN_KNRM_RATING,
		CLMN_KNRM_CNT,
		CLMN_IMDB_RATING,
		CLMN_IMDB_CNT,
		CLMN_PREMIER_WORLD,
		CLMN_PREMIER_RU,
		CLMN_PREMIER_DG,
		CLMN_ACTORS,
		CLMN_DIRECTORS,
		CLMN_NOTE,
		NUM_OF_COLUMNS
	};
};

} // namespace Movies
