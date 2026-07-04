#include "BaseExtraConverter.h"
#include "BaseExtraList.h"

#include <storage/csv/CsvData.h>

QStringList Base::ExtraConverter::getDefaultCsvHeader()
{
	QStringList header(NUM_OF_COLUMNS);

	header[CLMN_GROUP] = tr("Список");
	header[CLMN_TITLE] = tr("Запись");
	header[CLMN_NOTES] = tr("Комментарий");

	return header;
}

Base::ExtraList Base::ExtraConverter::conv(const Csv::Data& csv_data)
{
	ExtraList data_list;

	for (const auto& line : csv_data) {
		int line_size = line.size();
		Extra data;

		if (CLMN_GROUP < line_size) {
			data.setGroup(line[CLMN_GROUP]);
		}
		if (CLMN_TITLE < line_size) {
			data.setTitle(line[CLMN_TITLE]);
		}
		if (CLMN_NOTES < line_size) {
			data.setNotes(line[CLMN_NOTES]);
		}

		data_list.add(data);
	}

	return data_list;
}

Csv::Data Base::ExtraConverter::conv(const ExtraList& data_list)
{
	Csv::Data csv_data;

	for (const auto& data : data_list) {
		QStringList line(NUM_OF_COLUMNS);

		line[CLMN_GROUP] = data.group();
		line[CLMN_TITLE] = data.title();
		line[CLMN_NOTES] = data.notes();

		csv_data.push_back(line);
	}

	return csv_data;
}
