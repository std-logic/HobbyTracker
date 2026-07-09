#include "BikeDataConverter.h"
#include "BikeDataList.h"

#include <storage/csv/CsvData.h>

QStringList Bike::DataConverter::getDefaultCsvHeader()
{
	QStringList header(NUM_OF_COLUMNS);

	header[CLMN_YEAR]		= tr("Год");
	header[CLMN_TIME]		= tr("Часов");
	header[CLMN_DIST]		= tr("Километров");

	return header;
}

Bike::DataList Bike::DataConverter::conv(const Csv::Data& csv_data)
{
	DataList data_list;
	bool conv_ok;

	for (const auto& line : csv_data) {
		int line_size = line.size();
		Data data;

		if (CLMN_YEAR < line_size) {
			auto year = line[CLMN_YEAR].toUInt(&conv_ok);
			if (conv_ok) { data.setYear(year); }
		}
		if (CLMN_TIME < line_size) {
			auto time = line[CLMN_TIME].toUInt(&conv_ok);
			if (conv_ok) { data.setTime(time); }
		}
		if (CLMN_DIST < line_size) {
			auto dist = line[CLMN_DIST].toUInt(&conv_ok);
			if (conv_ok) { data.setDist(dist); }
		}

		data_list.add(data);
	}

	return data_list;
}

Csv::Data Bike::DataConverter::conv(const DataList& data_list)
{
	Csv::Data csv_data;

	for (const auto& data : data_list) {
		QStringList line(NUM_OF_COLUMNS);

		line[CLMN_YEAR]		= QString::number(data.year());
		line[CLMN_TIME]		= QString::number(data.time());
		line[CLMN_DIST]		= QString::number(data.dist());

		csv_data.push_back(line);
	}

	return csv_data;
}
