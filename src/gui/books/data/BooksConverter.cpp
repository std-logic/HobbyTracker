#include "BooksConverter.h"
#include "BooksDataList.h"

#include <storage/csv/CsvData.h>

QStringList Books::Converter::getDefaultCsvHeader()
{
	QStringList header;
	for (int i = 0; i < NUM_OF_COLUMNS; ++i) {
		header += QString();
	}

	header[CLMN_AUTHOR_TR] = tr("Автор (пер.)");
	header[CLMN_AUTHOR_ORIG] = tr("Автор (ориг.)");
	header[CLMN_TITLE_TR] = tr("Произведение (пер.)");
	header[CLMN_TITLE_ORIG] = tr("Произведение (ориг.)");
	header[CLMN_GENRE] = tr("Жанр");
	header[CLMN_YEAR] = tr("Год");
	header[CLMN_RATING] = tr("Оценка");

	return header;
}

Books::DataList Books::Converter::conv(const Csv::Data& csv_data)
{
	DataList data_list;
	bool conv_ok;

	for (const auto& line : csv_data) {
		int line_size = line.size();
		Data data;

		if (CLMN_AUTHOR_TR < line_size) {
			data.setAuthorTr(line[CLMN_AUTHOR_TR]);
		}
		if (CLMN_AUTHOR_ORIG < line_size) {
			data.setAuthorOrig(line[CLMN_AUTHOR_ORIG]);
		}
		if (CLMN_TITLE_TR < line_size) {
			data.setTitleTr(line[CLMN_TITLE_TR]);
		}
		if (CLMN_TITLE_ORIG < line_size) {
			data.setTitleOrig(line[CLMN_TITLE_ORIG]);
		}
		if (CLMN_GENRE < line_size) {
			data.setGenre(line[CLMN_GENRE]);
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

Csv::Data Books::Converter::conv(const DataList& /*data_list*/)
{
	Csv::Data csv_data;







	return csv_data;
}
