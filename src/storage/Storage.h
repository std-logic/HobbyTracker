#pragma once

#include <QObject>

namespace Csv
{
class Data;
class Settings;
}

class Storage : public QObject
{
	Q_OBJECT
public:
	explicit Storage(QObject* parent = nullptr);
	~Storage() = default;

public slots:
	void readCsv(const Csv::Settings& csv_settings);
	void writeCsv(const Csv::Settings& csv_settings, const Csv::Data& csv_data);

signals:
	void dataCsv(const Csv::Settings& csv_settings, const Csv::Data& csv_data);
};
