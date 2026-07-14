#include "MusicDataConverter.h"
#include "MusicDataList.h"

#include <storage/csv/CsvData.h>

QStringList Music::DataConverter::getDefaultCsvHeader()
{
	QStringList header(NUM_OF_COLUMNS);

	header[CLMN_TITLE]			= tr("Название");
	header[CLMN_GENRE]			= tr("Жанр");
	header[CLMN_COUNTRY]		= tr("Страна основания");
	header[CLMN_YEAR]			= tr("Год основания");
	header[CLMN_STATE]			= tr("Статус");

	return header;
}

Music::DataList Music::DataConverter::conv(const Csv::Data& csv_data)
{
	DataList data_list;
	bool conv_ok;

	for (const auto& line : csv_data) {
		int line_size = line.size();
		Data data;

		if (CLMN_TITLE < line_size) {
			data.setTitle(line[CLMN_TITLE]);
		}
		if (CLMN_GENRE < line_size) {
			data.setGenre(line[CLMN_GENRE]);
		}
		if (CLMN_COUNTRY < line_size) {
			data.setCountry(line[CLMN_COUNTRY]);
		}
		if (CLMN_YEAR < line_size) {
			auto year = line[CLMN_YEAR].toUInt(&conv_ok);
			if (conv_ok) { data.setYear(year); }
		}
		if (CLMN_STATE < line_size) {
			auto state = line[CLMN_STATE].toUInt(&conv_ok);
			if (conv_ok) { data.setState(static_cast<States>(state)); }
		}

		data_list.add(data);
	}

	return data_list;
}

Csv::Data Music::DataConverter::conv(const DataList& data_list)
{
	Csv::Data csv_data;

	for (const auto& data : data_list) {
		QStringList line(NUM_OF_COLUMNS);

		line[CLMN_TITLE]		= data.title();
		line[CLMN_GENRE]		= data.genre();
		line[CLMN_COUNTRY]		= data.country();
		line[CLMN_YEAR]			= QString::number(data.year());
		line[CLMN_STATE]		= QString::number(data.state());

		csv_data.push_back(line);
	}

	return csv_data;
}
