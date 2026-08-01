#include "MoviesFavoritesConverter.h"
#include "MoviesDataList.h"

#include <storage/csv/CsvData.h>

QStringList Movies::FavoritesConverter::getDefaultCsvHeader()
{
	QStringList header(NUM_OF_COLUMNS);

	header[CLMN_TITLE_TR]		= tr("Название (пер.)");
	header[CLMN_TITLE_ORIG]		= tr("Название (ориг.)");
	header[CLMN_YEAR]			= tr("Год");
	header[CLMN_GENRES]			= tr("Жанр");
	header[CLMN_COUNTRIES]		= tr("Страна");
	header[CLMN_DIRECTORS]		= tr("Режиссёр");
	header[CLMN_WRITERS]		= tr("Сценарист");
	header[CLMN_ACTORS]			= tr("Актёры");

	return header;
}

Movies::DataList Movies::FavoritesConverter::conv(const Csv::Data& csv_data)
{
	DataList data_list;
	bool conv_ok;

	for (const auto& line : csv_data) {
		int line_size = line.size();
		Data data;

		if (CLMN_TITLE_TR < line_size) {
			data.setTitleTr(line[CLMN_TITLE_TR]);
		}
		if (CLMN_TITLE_ORIG < line_size) {
			data.setTitleOrig(line[CLMN_TITLE_ORIG]);
		}
		if (CLMN_YEAR < line_size) {
			auto year = line[CLMN_YEAR].toUInt(&conv_ok);
			if (conv_ok) { data.setYear(year); }
		}
		if (CLMN_GENRES < line_size) {
			data.setGenresFromString(line[CLMN_GENRES]);
		}
		if (CLMN_COUNTRIES < line_size) {
			data.setCountriesFromString(line[CLMN_COUNTRIES]);
		}
		if (CLMN_DIRECTORS < line_size) {
			data.setDirectorsFromString(line[CLMN_DIRECTORS]);
		}
		if (CLMN_WRITERS < line_size) {
			data.setWritersFromString(line[CLMN_WRITERS]);
		}
		if (CLMN_ACTORS < line_size) {
			data.setActorsFromString(line[CLMN_ACTORS]);
		}

		data_list.add(data);
	}

	return data_list;
}

Csv::Data Movies::FavoritesConverter::conv(const DataList& data_list)
{
	Csv::Data csv_data;

	for (const auto& data : data_list) {
		QStringList line(NUM_OF_COLUMNS);

		line[CLMN_TITLE_TR]			= data.titleTr();
		line[CLMN_TITLE_ORIG]		= data.titleOrig();
		line[CLMN_YEAR]				= data.yearString();
		line[CLMN_GENRES]			= data.genresToString();
		line[CLMN_COUNTRIES]		= data.countriesToString();
		line[CLMN_DIRECTORS]		= data.directorsToString();
		line[CLMN_WRITERS]			= data.writersToString();
		line[CLMN_ACTORS]			= data.actorsToString();

		csv_data.push_back(line);
	}

	return csv_data;
}
