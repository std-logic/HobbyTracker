#include "GamesDataConverter.h"
#include "GamesDataList.h"

#include <storage/csv/CsvData.h>

QStringList Games::DataConverter::getDefaultCsvHeader()
{
	QStringList header(NUM_OF_COLUMNS);

	header[CLMN_SERIES]			= tr("Серия");
	header[CLMN_TITLE]			= tr("Игра");
	header[CLMN_GENRE]			= tr("Жанр");
	header[CLMN_DEVELOPER]		= tr("Разработчик");
	header[CLMN_YEAR]			= tr("Год");
	header[CLMN_RATING]			= tr("Оценка");

	return header;
}

Games::DataList Games::DataConverter::conv(const Csv::Data& csv_data)
{
	DataList data_list;
	bool conv_ok;

	for (const auto& line : csv_data) {
		int line_size = line.size();
		Data data;

		if (CLMN_SERIES < line_size) {
			data.setSeries(line[CLMN_SERIES]);
		}
		if (CLMN_TITLE < line_size) {
			data.setTitle(line[CLMN_TITLE]);
		}
		if (CLMN_GENRE < line_size) {
			data.setGenre(line[CLMN_GENRE]);
		}
		if (CLMN_DEVELOPER < line_size) {
			data.setDeveloper(line[CLMN_DEVELOPER]);
		}
		if (CLMN_YEAR < line_size) {
			auto year = line[CLMN_YEAR].toUInt(&conv_ok);
			if (conv_ok) { data.setYear(year); }
		}
		if (CLMN_RATING < line_size) {
			auto rating = line[CLMN_RATING].toUInt(&conv_ok);
			if (conv_ok) { data.setRating(rating); }
		}

		data_list.add(data);
	}

	return data_list;
}

Csv::Data Games::DataConverter::conv(const DataList& data_list)
{
	Csv::Data csv_data;

	for (const auto& data : data_list) {
		QStringList line(NUM_OF_COLUMNS);

		line[CLMN_SERIES]		= data.series();
		line[CLMN_TITLE]		= data.title();
		line[CLMN_GENRE]		= data.genre();
		line[CLMN_DEVELOPER]	= data.developer();
		line[CLMN_YEAR]			= QString::number(data.year());
		line[CLMN_RATING]		= QString::number(data.rating());

		csv_data.push_back(line);
	}

	return csv_data;
}
