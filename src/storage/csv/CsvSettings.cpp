#include "CsvSettings.h"

#include <QSettings>

void Csv::Settings::save(QSettings* settings, const QString& group_name) const
{
	settings->beginGroup(group_name);

	for (size_t i = 0; i < _file_name.size(); ++i) {
		settings->setValue("file_name_" + QString::number(i), _file_name[i]);
	}
	settings->setValue("encoding", _encoding);
	settings->setValue("delimiter", QString(_delimiter));
	settings->setValue("skip_at_start", _skip_at_start);

	settings->endGroup();
}

void Csv::Settings::load(QSettings* settings, const QString& group_name)
{
	settings->beginGroup(group_name);

	for (size_t i = 0; i < 100; ++i) {
		auto value_name = "file_name_" + QString::number(i);
		if (settings->contains(value_name)) {
			setFileName(i, settings->value(value_name).toString());
		} else {
			break;
		}
	}
	_encoding = static_cast<QStringConverter::Encoding>(
				settings->value("encoding", QStringConverter::Utf8).toInt());
	auto delimiter_str = settings->value("delimiter", QString(';')).toString();
	_delimiter = !delimiter_str.isEmpty() ? delimiter_str.front() : ';';
	_skip_at_start = settings->value("skip_at_start", 1).toInt();

	settings->endGroup();
}
