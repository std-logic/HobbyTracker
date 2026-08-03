#include "MoviesDataConverter.h"
#include "MoviesDataList.h"

#include <storage/csv/CsvData.h>

QStringList Movies::DataConverter::getDefaultCsvHeader()
{
	QStringList header(NUM_OF_COLUMNS);

	header[CLMN_RATING]			= tr("My rating");
	header[CLMN_BACKUP_ID]		= tr("backup_id");
	header[CLMN_VIEW_DATE]		= tr("Date");
	header[CLMN_TITLE_TR]		= tr("Title");
	header[CLMN_TITLE_ORIG]		= tr("Original Title");
	header[CLMN_KIND]			= tr("Type");
	header[CLMN_YEAR]			= tr("Year");
	header[CLMN_GENRES]			= tr("Genres");
	header[CLMN_COUNTRIES]		= tr("Countries");
	header[CLMN_TIME]			= tr("Runtime");
	header[CLMN_AGE_LIMIT]		= tr("Age limit");
	header[CLMN_MPAA]			= tr("MPAA");
	header[CLMN_BUDGET]			= tr("Budget");
	header[CLMN_BOX_USA]		= tr("Box USA");
	header[CLMN_BOX_WORLD]		= tr("Box world");
	header[CLMN_BOX_RU]			= tr("Box RU");
	header[CLMN_AUDIENCE]		= tr("Audience");
	header[CLMN_KNRM_RATING]	= tr("Knrm rating");
	header[CLMN_KNRM_CNT]		= tr("Knrm cnt");
	header[CLMN_IMDB_RATING]	= tr("IMDb rating");
	header[CLMN_IMDB_CNT]		= tr("IMDb cnt");
	header[CLMN_PREMIER_WORLD]	= tr("World premier date");
	header[CLMN_PREMIER_RU]		= tr("RU premier date");
	header[CLMN_PREMIER_DG]		= tr("Digital premier date");
	header[CLMN_ACTORS]			= tr("Actors");
	header[CLMN_DIRECTORS]		= tr("Directors");
	header[CLMN_NOTE]			= tr("Note");

	return header;
}

Movies::DataList Movies::DataConverter::conv(const Csv::Data& csv_data)
{
	DataList data_list;
	bool conv_ok;

	for (const auto& line : csv_data) {
		int line_size = line.size();
		Data data;

		if (CLMN_RATING < line_size) {
			auto rating = line[CLMN_RATING].toUInt(&conv_ok);
			if (conv_ok) { data.setRating(rating); }
		}
		if (CLMN_VIEW_DATE < line_size) {
			auto view_date = line[CLMN_VIEW_DATE];
			data.setViewDate(view_date.replace(QChar('-'), QChar('.')));
		}
		if (CLMN_TITLE_TR < line_size) {
			data.setTitleTr(line[CLMN_TITLE_TR]);
		}
		if (CLMN_TITLE_ORIG < line_size) {
			data.setTitleOrig(line[CLMN_TITLE_ORIG]);
		}
		if (CLMN_KIND < line_size) {
			data.setKind(line[CLMN_KIND]);
		}
		if (CLMN_YEAR < line_size) {
			data.setYearFromString(line[CLMN_YEAR]);
		}
		if (CLMN_GENRES < line_size) {
			data.setGenresFromString(line[CLMN_GENRES]);
		}
		if (CLMN_COUNTRIES < line_size) {
			data.setCountriesFromString(line[CLMN_COUNTRIES]);
		}
		if (CLMN_TIME < line_size) {
			auto time = line[CLMN_TIME].toUInt(&conv_ok);
			if (conv_ok) { data.setTime(time); }
		}
		if (CLMN_ACTORS < line_size) {
			data.setActorsFromString(line[CLMN_ACTORS]);
		}
		if (CLMN_DIRECTORS < line_size) {
			data.setDirectorsFromString(line[CLMN_DIRECTORS]);
		}

		data_list.add(data);
	}

	return data_list;
}

Csv::Data Movies::DataConverter::conv(const DataList& data_list)
{
	Csv::Data csv_data;

	for (const auto& data : data_list) {
		QStringList line(NUM_OF_COLUMNS);

		line[CLMN_RATING]			= QString::number(data.rating());
		line[CLMN_VIEW_DATE]		= data.viewDate().replace(QChar('.'), QChar('-'));
		line[CLMN_TITLE_TR]			= data.titleTr();
		line[CLMN_TITLE_ORIG]		= data.titleOrig();
		line[CLMN_KIND]				= data.kind();
		line[CLMN_YEAR]				= data.yearString();
		line[CLMN_GENRES]			= data.genresToString();
		line[CLMN_COUNTRIES]		= data.countriesToString();
		line[CLMN_TIME]				= QString::number(data.time());
		line[CLMN_ACTORS]			= data.actorsToString();
		line[CLMN_DIRECTORS]		= data.directorsToString();

		csv_data.push_back(line);
	}

	return csv_data;
}
