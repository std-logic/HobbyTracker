#pragma once

#include <common/Global.h>
#include <common/Helper.h>

#include <QString>

namespace Books
{

class Data
{
public:
	Data() = default;

	void clear()
	{ *this = Data(); }

	inline void setAuthorTr(const QString& author_tr)
	{ _author_tr = author_tr; }
	inline void setAuthorTr(QString&& author_tr)
	{ _author_tr = std::move(author_tr); }
	inline QString authorTr() const
	{ return _author_tr; }

	inline void setAuthorOrig(const QString& author_orig)
	{ _author_orig = author_orig; }
	inline void setAuthorOrig(QString&& author_orig)
	{ _author_orig = std::move(author_orig); }
	inline QString authorOrig() const
	{ return _author_orig; }

	inline QString author() const
	{ return Helper::fullTrAndOrigString(_author_tr, _author_orig); }

	inline void setTitleTr(const QString& title_tr)
	{ _title_tr = title_tr; }
	inline void setTitleTr(QString&& title_tr)
	{ _title_tr = std::move(title_tr); }
	inline QString titleTr() const
	{ return _title_tr; }

	inline void setTitleOrig(const QString& title_orig)
	{ _title_orig = title_orig; }
	inline void setTitleOrig(QString&& title_orig)
	{ _title_orig = std::move(title_orig); }
	inline QString titleOrig() const
	{ return _title_orig; }

	inline QString title() const
	{ return Helper::fullTrAndOrigString(_title_tr, _title_orig); }

	inline QString autorAndTitle() const
	{ return QStringLiteral("%1 - %2").arg(author(), title()); }

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
	QString yearString(const QString& undefined_string = QString()) const
	{ return (_year == Global::undefined_value) ? undefined_string : QString::number(_year); }

	inline void setRating(uint32_t rating)
	{ _rating = rating; }
	inline uint32_t rating() const
	{ return _rating; }
	QString ratingString(const QString& undefined_string = QString()) const
	{ return (_rating == Global::undefined_value) ? undefined_string : QString::number(_rating); }

private:
	QString _author_tr;
	QString _author_orig;
	QString _title_tr;
	QString _title_orig;
	QString _genre;
	uint32_t _year = Global::undefined_value;
	uint8_t _rating = Global::undefined_value;
};

} // namespace Books
