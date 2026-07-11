#include "FlightsDataConverter.h"
#include "FlightsDataList.h"

#include <storage/csv/CsvData.h>

QStringList Flights::DataConverter::getDefaultCsvHeader()
{
	QStringList header(NUM_OF_COLUMNS);

	header[CLMN_DATE]	= tr("Дата");
	for (int i = CLMN_POINT_FIRST; i <= CLMN_POINT_LAST; ++i) {
		header[i]		= tr("Точка %1").arg(i - CLMN_POINT_FIRST + 1);
	}

	return header;
}

Flights::DataList Flights::DataConverter::conv(const Csv::Data& csv_data)
{
	DataList data_list;

	for (const auto& line : csv_data) {
		int line_size = line.size();
		Data data;

		if (CLMN_DATE < line_size) {
			data.setDate(line[CLMN_DATE]);
		}
		for (int i = CLMN_POINT_FIRST; i <= CLMN_POINT_LAST; ++i) {
			if (i < line_size) {
				data.addPointFromString(line[i]);
			}
		}

		data_list.add(data);
	}

	return data_list;
}

Csv::Data Flights::DataConverter::conv(const DataList& data_list)
{
	Csv::Data csv_data;

	for (const auto& data : data_list) {
		QStringList line(NUM_OF_COLUMNS);

		line[CLMN_DATE]		= data.date();
		for (int i = CLMN_POINT_FIRST; i <= CLMN_POINT_LAST; ++i) {
			line[i]			= data.pointToString(i - CLMN_POINT_FIRST);
		}

		csv_data.push_back(line);
	}

	return csv_data;
}
