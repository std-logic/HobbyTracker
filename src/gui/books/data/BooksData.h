#pragma once

#include <common/Global.h>

#include <QString>

namespace Books
{

class Data
{
public:
	Data() = default;

	inline void setAuthor(const QString& author)
	{ _author = author; }
	inline void setAuthor(QString&& author)
	{ _author = std::move(author); }
	inline QString author() const
	{ return _author; }

	inline void setTitle(const QString& title)
	{ _title = title; }
	inline void setTitle(QString&& title)
	{ _title = std::move(title); }
	inline QString title() const
	{ return _title; }

	inline void setGenre(const QString& genre)
	{ _genre = genre; }
	inline void setGenre(QString&& genre)
	{ _genre = std::move(genre); }
	inline QString genre() const
	{ return _genre; }

	inline void setYear(uint32_t year)
	{ _year = year; }
	inline uint32_t year() const
	{ return _year; }
	QString yearString() const
	{ return (_year == Global::undefined_value) ? QString() : QString::number(_year); }

	inline void setRating(uint32_t rating)
	{ _rating = rating; }
	inline uint32_t rating() const
	{ return _rating; }
	QString ratingString() const
	{ return (_rating == Global::undefined_value) ? QString() : QString::number(_rating); }

private:
	QString _author;
	QString _title;
	QString _genre;
	uint32_t _year = Global::undefined_value;
	uint8_t _rating = Global::undefined_value;
};

} // namespace Books
