#include "CoinsDataConverter.h"
#include "CoinsDataList.h"

#include <storage/csv/CsvData.h>

QStringList Coins::DataConverter::getDefaultCsvHeader()
{
	QStringList header(NUM_OF_COLUMNS);

	header[CLMN_COUNTRY]		= tr("Страна");
	header[CLMN_PERIOD]			= tr("Период");
	header[CLMN_VALUE]			= tr("Номинал");
	header[CLMN_YEAR]			= tr("Год");
	header[CLMN_VERSION]		= tr("Var.");
	header[CLMN_CURRENCY]		= tr("Валюта");
	header[CLMN_TITLE]			= tr("Наименование");
	header[CLMN_DIAMETER]		= tr("Диаметр, mm");
	header[CLMN_STATE]			= tr("Состояние");
	header[CLMN_PRICE]			= tr("Цена, USD");
	header[CLMN_NUMBER]			= tr("Номер");
	header[CLMN_LABEL]			= tr("Метка");
	header[CLMN_COMMENT]		= tr("Комментарий");

	return header;
}

Coins::DataList Coins::DataConverter::conv(const Csv::Data& csv_data)
{
	DataList data_list;
	bool conv_ok;

	for (const auto& line : csv_data) {
		int line_size = line.size();
		Data data;

		if (CLMN_COUNTRY < line_size) {
			data.setCountry(line[CLMN_COUNTRY]);
		}
		if (CLMN_PERIOD < line_size) {
			data.setPeriod(line[CLMN_PERIOD]);
		}
		if (CLMN_VALUE < line_size) {
			data.setValue(line[CLMN_VALUE]);
		}
		if (CLMN_YEAR < line_size) {
			if (line[CLMN_YEAR].size() >= 4) {
				auto year = line[CLMN_YEAR].first(4).toUInt(&conv_ok);
				if (conv_ok) { data.setYear(year); }
			}
		}
		if (CLMN_VERSION < line_size) {
			data.setVersion(line[CLMN_VERSION]);
		}
		if (CLMN_CURRENCY < line_size) {
			data.setCurrency(line[CLMN_CURRENCY]);
		}
		if (CLMN_TITLE < line_size) {
			data.setTitle(line[CLMN_TITLE]);
		}
		if (CLMN_DIAMETER < line_size) {
			data.setDiameter(line[CLMN_DIAMETER]);
		}
		if (CLMN_STATE < line_size) {
			data.setState(line[CLMN_STATE]);
		}
		if (CLMN_NUMBER < line_size) {
			data.setNumber(line[CLMN_NUMBER]);
		}

		data_list.add(data);
	}

	return data_list;
}

Csv::Data Coins::DataConverter::conv(const DataList& data_list)
{
	Csv::Data csv_data;

	for (const auto& data : data_list) {
		QStringList line(NUM_OF_COLUMNS);

		line[CLMN_COUNTRY]			= data.country();
		line[CLMN_PERIOD]			= data.period();
		line[CLMN_VALUE]			= data.value();
		line[CLMN_YEAR]				= data.yearString();
		line[CLMN_VERSION]			= data.version();
		line[CLMN_CURRENCY]			= data.currency();
		line[CLMN_TITLE]			= data.title();
		line[CLMN_DIAMETER]			= data.diameter();
		line[CLMN_STATE]			= data.state();
		line[CLMN_NUMBER]			= data.number();

		csv_data.push_back(line);
	}

	return csv_data;
}
