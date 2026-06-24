#include "CsvStorage.h"

#include <QFile>
#include <QTextStream>

void Csv::Storage::createFile(const Settings& csv_settings)
{
	if (QFile::exists(csv_settings.fileName())) {
		return;
	}

	QFile file(csv_settings.fileName());
	if (!file.open(QFile::WriteOnly | QFile::Text)) {
		return;
	}

	auto header = csv_settings.header();
	if (!header.isEmpty()) {
		QTextStream stream(&file);
		stream.setEncoding(csv_settings.encoding());
		stream.setGenerateByteOrderMark(csv_settings.addBom());
		for (int column = 0; column < header.size(); ++column) {
			stream << header[column];
			if (column != (header.size() - 1)) {
				stream << csv_settings.delimiter();
			}
		}
		stream << csv_settings.ending();
	}

	file.close();
}

Csv::Data Csv::Storage::readFile(const Settings& csv_settings)
{
	Data csv_data;

	QFile file(csv_settings.fileName());
	if (!file.open(QFile::ReadOnly | QFile::Text)) {
		return csv_data;
	}

	QTextStream stream(&file);
	stream.setEncoding(csv_settings.encoding());
	for (int line = 0; line < csv_settings.skipAtStart(); ++line) {
		stream.readLine();
	}
	QString buff;
	while (stream.readLineInto(&buff)) {
		csv_data.push_back(buff.remove(QChar('\"')).split(csv_settings.delimiter()));
	}

	file.close();
	return csv_data;
}

void Csv::Storage::writeFile(const Settings& /*csv_settings*/, const Data& /*csv_data*/)
{

}
