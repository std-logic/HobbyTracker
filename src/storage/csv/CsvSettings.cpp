#include "CsvSettings.h"

#include <QSettings>

void Csv::Settings::save(QSettings* settings, const QString& group_name) const
{
	settings->beginGroup(group_name);

	settings->setValue("file_name", _file_name);
	settings->setValue("encoding", _encoding);
	settings->setValue("delimiter", QString(_delimiter));
	settings->setValue("skip_at_start", _skip_at_start);

	settings->endGroup();
}

void Csv::Settings::load(QSettings* settings, const QString& group_name)
{
	settings->beginGroup(group_name);

	_file_name = settings->value("file_name").toString();
	_encoding = static_cast<QStringConverter::Encoding>(
				settings->value("encoding", QStringConverter::Utf8).toInt());
	auto delimiter_str = settings->value("delimiter", QString(';')).toString();
	_delimiter = !delimiter_str.isEmpty() ? delimiter_str.front() : ';';
	_skip_at_start = settings->value("skip_at_start", 1).toInt();

	settings->endGroup();
}
