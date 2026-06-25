#include "BooksConverter.h"
#include "BooksDataList.h"

#include <storage/csv/CsvData.h>

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

Csv::Data Books::Converter::conv(const DataList& data_list)
{
	Csv::Data csv_data;







	return csv_data;
}
