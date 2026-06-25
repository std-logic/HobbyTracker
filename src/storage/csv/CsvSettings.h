#pragma once

#include <QString>
#include <QStringList>

class QSettings;

namespace Csv
{

class Settings
{
public:
	Settings() = default;

	void save(QSettings* settings) const;
	void load(QSettings* settings);

	inline void setFileName(const QString& file_name)
	{ _file_name = file_name; }
	inline void setFileName(QString&& file_name)
	{ _file_name = std::move(file_name); }
	inline QString fileName() const
	{ return _file_name; }
	inline bool isFileNameEqual(QString&& file_name) const
	{ return (_file_name == file_name); }

	inline void setEncoding(QStringConverter::Encoding encoding)
	{ _encoding = encoding; }
	inline QStringConverter::Encoding encoding() const
	{ return _encoding; }

	inline void setAddBom(bool add_bom)
	{ _add_bom = add_bom; }
	inline bool addBom() const
	{ return _add_bom; }

	inline void setDelimiter(QChar delimiter)
	{ _delimiter = delimiter; }
	inline QChar delimiter() const
	{ return _delimiter; }

	inline void setEnding(QChar ending)
	{ _ending = ending; }
	inline QChar ending() const
	{ return _ending; }

	inline void setSkipAtStart(int skip_at_start)
	{ _skip_at_start = skip_at_start; }
	inline int skipAtStart() const
	{ return _skip_at_start; }

	inline void setHeader(const QStringList& header)
	{ _header = header; }
	inline void setHeader(QStringList&& header)
	{ _header = std::move(header); }
	inline QStringList header() const
	{ return _header; }

private:
	QString _file_name;
	QStringConverter::Encoding _encoding = QStringConverter::Utf8;
	bool _add_bom = true;
	QChar _delimiter = ';';
	QChar _ending = '\n';
	int _skip_at_start = 1;
	QStringList _header;
};

} // namespace Csv
