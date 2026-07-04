#pragma once

#include <QString>
#include <QStringList>

#include <vector>

class QSettings;

namespace Csv
{

class Settings
{
public:
	Settings() = default;

	void save(QSettings* settings, const QString& group_name) const;
	void load(QSettings* settings, const QString& group_name);

	template<typename T>
	inline void setHeader(size_t index, T&& header)
	{
		if (index < _header.size()) {
			_header[index] = std::forward<T>(header);
		} else {
			_header.emplace_back(std::forward<T>(header));
		}
	}
	inline QStringList header(size_t index) const
	{ return (index < _header.size()) ?_header[index] : QStringList(); }

	template<typename T>
	inline void setFileName(size_t index, T&& file_name)
	{
		if (index < _file_name.size()) {
			_file_name[index] = std::forward<T>(file_name);
		} else {
			_file_name.emplace_back(std::forward<T>(file_name));
		}
	}
	inline QString fileName(size_t index) const
	{ return (index < _file_name.size()) ?_file_name[index] : QString(); }

	inline size_t numOfFiles() const
	{ return _file_name.size(); }

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

private:
	std::vector<QStringList> _header; // not stored in file, but convenient to have nearby
	std::vector<QString> _file_name;
	QStringConverter::Encoding _encoding = QStringConverter::Utf8;
	bool _add_bom = true;
	QChar _delimiter = ';';
	QChar _ending = '\n';
	int _skip_at_start = 1;
};

} // namespace Csv
