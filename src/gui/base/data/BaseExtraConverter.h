#pragma once

#include <QStringList>
#include <QCoreApplication>

namespace Csv
{
class Data;
}

namespace Base
{

class ExtraList;

class ExtraConverter
{
	Q_DECLARE_TR_FUNCTIONS(ExtraConverter)
public:
	ExtraConverter() = delete;

	static QStringList getDefaultCsvHeader();

	static ExtraList conv(const Csv::Data& csv_data);
	static Csv::Data conv(const ExtraList& data_list);

private:
	enum Columns
	{
		CLMN_GROUP,
		CLMN_TITLE,
		CLMN_NOTES,
		NUM_OF_COLUMNS
	};
};

} // namespace Base
