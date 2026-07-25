#include "ConcertsDataConverter.h"
#include "ConcertsDataList.h"

#include <storage/csv/CsvData.h>

QStringList Concerts::DataConverter::getDefaultCsvHeader()
{
	QStringList header(NUM_OF_COLUMNS);

	header[CLMN_DATE]			= tr("Дата");
	header[CLMN_ARTISTS]		= tr("Группы");
	header[CLMN_KINDS]			= tr("Типы");
	header[CLMN_COUNTRY]		= tr("Страна");
	header[CLMN_CITY]			= tr("Город");
	header[CLMN_PLACE]			= tr("Место");

	return header;
}

Concerts::DataList Concerts::DataConverter::conv(const Csv::Data& csv_data)
{
	DataList data_list;

	for (const auto& line : csv_data) {
		int line_size = line.size();
		Data data;

		if (CLMN_DATE < line_size) {
			data.setDate(line[CLMN_DATE]);
		}
		if (CLMN_ARTISTS < line_size) {
			data.setArtistsFromString(line[CLMN_ARTISTS]);
		}
		if (CLMN_KINDS < line_size) {
			data.setKindsFromString(line[CLMN_KINDS]);
		}
		if (CLMN_COUNTRY < line_size) {
			data.setCountry(line[CLMN_COUNTRY]);
		}
		if (CLMN_CITY < line_size) {
			data.setCity(line[CLMN_CITY]);
		}
		if (CLMN_PLACE < line_size) {
			data.setPlace(line[CLMN_PLACE]);
		}

		data_list.add(data);
	}

	return data_list;
}

Csv::Data Concerts::DataConverter::conv(const DataList& data_list)
{
	Csv::Data csv_data;

	for (const auto& data : data_list) {
		QStringList line(NUM_OF_COLUMNS);

		line[CLMN_DATE]			= data.date();
		line[CLMN_ARTISTS]		= data.artistsToString();
		line[CLMN_KINDS]		= data.kindsToString();
		line[CLMN_COUNTRY]		= data.country();
		line[CLMN_CITY]			= data.city();
		line[CLMN_PLACE]		= data.place();

		csv_data.push_back(line);
	}

	return csv_data;
}
