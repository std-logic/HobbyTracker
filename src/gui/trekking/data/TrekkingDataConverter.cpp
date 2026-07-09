#include "TrekkingDataConverter.h"
#include "TrekkingDataList.h"

#include <storage/csv/CsvData.h>

QStringList Trekking::DataConverter::getDefaultCsvHeader()
{
	QStringList header(NUM_OF_COLUMNS);

	header[CLMN_DATE_START]		= tr("Старт");
	header[CLMN_DATE_END]		= tr("Финиш");
	header[CLMN_TIME]			= tr("Ночёвок");
	header[CLMN_DIST]			= tr("Километров");
	header[CLMN_PEAK]			= tr("Высшая точка");
	header[CLMN_KIND]			= tr("Тип");
	header[CLMN_COUNTRIES]		= tr("Страны");
	header[CLMN_PLACES]			= tr("Место");

	return header;
}

Trekking::DataList Trekking::DataConverter::conv(const Csv::Data& csv_data)
{
	DataList data_list;
	bool conv_ok;

	for (const auto& line : csv_data) {
		int line_size = line.size();
		Data data;

		if (CLMN_DATE_START < line_size) {
			data.setDateStart(line[CLMN_DATE_START]);
		}
		if (CLMN_DATE_END < line_size) {
			data.setDateEnd(line[CLMN_DATE_END]);
		}
		if (CLMN_TIME < line_size) {
			auto time = line[CLMN_TIME].toUInt(&conv_ok);
			if (conv_ok) { data.setTime(time); }
		}
		if (CLMN_DIST < line_size) {
			auto dist = line[CLMN_DIST].toUInt(&conv_ok);
			if (conv_ok) { data.setDist(dist); }
		}
		if (CLMN_PEAK < line_size) {
			auto peak = line[CLMN_PEAK].toUInt(&conv_ok);
			if (conv_ok) { data.setPeak(peak); }
		}
		if (CLMN_KIND < line_size) {
			data.setKind(line[CLMN_KIND]);
		}
		if (CLMN_COUNTRIES < line_size) {
			data.setCountriesFromString(line[CLMN_COUNTRIES]);
		}
		if (CLMN_PLACES < line_size) {
			data.setPlaces(line[CLMN_PLACES]);
		}

		data_list.add(data);
	}

	return data_list;
}

Csv::Data Trekking::DataConverter::conv(const DataList& data_list)
{
	Csv::Data csv_data;

	for (const auto& data : data_list) {
		QStringList line(NUM_OF_COLUMNS);

		line[CLMN_DATE_START]	= data.dateStart();
		line[CLMN_DATE_END]		= data.dateEnd();
		line[CLMN_TIME]			= QString::number(data.time());
		line[CLMN_DIST]			= QString::number(data.dist());
		line[CLMN_PEAK]			= QString::number(data.peak());
		line[CLMN_KIND]			= data.kind();
		line[CLMN_COUNTRIES]	= data.countriesToString();
		line[CLMN_PLACES]		= data.places();

		csv_data.push_back(line);
	}

	return csv_data;
}
