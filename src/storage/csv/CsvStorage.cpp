#include "CsvStorage.h"

#include <QFile>
#include <QTextStream>

void Csv::Storage::createFile(size_t index, const Settings& csv_settings)
{
	if (csv_settings.fileName(index).isEmpty()) {
		return;
	}

	if (QFile::exists(csv_settings.fileName(index))) {
		return;
	}

	QFile file(csv_settings.fileName(index));
	if (!file.open(QFile::WriteOnly | QFile::Text)) {
		return;
	}

	QTextStream stream(&file);
	stream.setEncoding(csv_settings.encoding());
	stream.setGenerateByteOrderMark(csv_settings.addBom());

	auto header = csv_settings.header(index);
	if (!header.isEmpty()) {
		for (int column = 0; column < header.size(); ++column) {
			stream << QChar('\"') << header[column] << QChar('\"');
			if (column != (header.size() - 1)) {
				stream << csv_settings.delimiter();
			}
		}
		stream << csv_settings.ending();
	}

	file.close();
}

Csv::Data Csv::Storage::readFile(size_t index, const Settings& csv_settings)
{
	Data csv_data;

	if (csv_settings.fileName(index).isEmpty()) {
		return csv_data;
	}

	QFile file(csv_settings.fileName(index));
	if (!file.open(QFile::ReadOnly | QFile::Text)) {
		return csv_data;
	}

	QTextStream stream(&file);
	stream.setEncoding(csv_settings.encoding());
	for (int line = 0; line < csv_settings.skipAtStart(); ++line) {
		stream.readLine();
	}

	QString buff;
	QString delimiter_with_quotes = QString("\"") + csv_settings.delimiter() + QString("\"");
	while (stream.readLineInto(&buff)) {
		if (buff.startsWith(QChar('\"'))) {
			csv_data.push_back(buff.split(delimiter_with_quotes));
			csv_data.back().replaceInStrings("\"", "");
		} else {
			csv_data.push_back(buff.remove(QChar('\"')).split(csv_settings.delimiter()));
		}
	}

	file.close();
	return csv_data;
}

bool Csv::Storage::writeFile(size_t index, const Settings& csv_settings, const Data& csv_data)
{
	if (csv_settings.fileName(index).isEmpty()) {
		return false;
	}

	QFile file(csv_settings.fileName(index));
	if (!file.open(QFile::WriteOnly | QFile::Text)) {
		return false;
	}

	QTextStream stream(&file);
	stream.setEncoding(csv_settings.encoding());
	stream.setGenerateByteOrderMark(csv_settings.addBom());

	auto header = csv_settings.header(index);
	if (!header.isEmpty()) {
		for (int column = 0; column < header.size(); ++column) {
			stream << QChar('\"') << header[column] << QChar('\"');
			if (column != (header.size() - 1)) {
				stream << csv_settings.delimiter();
			}
		}
		stream << csv_settings.ending();
	}

	for (const auto& line : csv_data) {
		for (int column = 0; column < line.size(); ++column) {
			stream << QChar('\"') << line[column] << QChar('\"');
			if (column != (line.size() - 1)) {
				stream << csv_settings.delimiter();
			}
		}
		stream << csv_settings.ending();
	}

	file.close();
	return true;
}
