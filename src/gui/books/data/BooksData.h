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

	template<typename T>
	inline void setAuthorTr(T&& author_tr)
	{ _author_tr = std::forward<T>(author_tr); }
	inline QString authorTr() const
	{ return _author_tr; }

	template<typename T>
	inline void setAuthorOrig(T&& author_orig)
	{ _author_orig = std::forward<T>(author_orig); }
	inline QString authorOrig() const
	{ return _author_orig; }

	inline QString author() const
	{ return Helper::fullTrAndOrigString(_author_tr, _author_orig); }

	template<typename T>
	inline void setTitleTr(T&& title_tr)
	{ _title_tr = std::forward<T>(title_tr); }
	inline QString titleTr() const
	{ return _title_tr; }

	template<typename T>
	inline void setTitleOrig(T&& title_orig)
	{ _title_orig = std::forward<T>(title_orig); }
	inline QString titleOrig() const
	{ return _title_orig; }

	inline QString title() const
	{ return Helper::fullTrAndOrigString(_title_tr, _title_orig); }

	inline QString autorAndTitleTr() const
	{ return QStringLiteral("%1 - %2").arg(_author_tr, _title_tr); }
	inline QString autorAndTitleOrig() const
	{
		return QStringLiteral("%1 - %2")
				.arg(!_author_orig.isEmpty() ? _author_orig : _author_tr,
					 !_title_orig.isEmpty() ? _title_orig : _title_tr);
	}
	inline QString autorAndTitle() const
	{
		QString res = autorAndTitleTr();
		if (!_author_orig.isEmpty() || !_title_orig.isEmpty()) {
			res += QStringLiteral(" (%1)").arg(autorAndTitleOrig());
		}
		return res;
	}

	template<typename T>
	inline void setGenre(T&& genre)
	{ _genre = std::forward<T>(genre); }
	inline QString genre() const
	{ return _genre; }

	inline void setYear(uint32_t year)
	{ _year = year; }
	inline uint32_t year() const
	{ return _year; }
	QString yearString() const
	{ return Helper::yearString(_year); }

	inline void setRating(uint32_t rating)
	{ _rating = rating; }
	inline uint32_t rating() const
	{ return _rating; }

	QString summaryString() const
	{
		QString text;
		text += autorAndTitleTr();
		if (!_author_orig.isEmpty() || !_title_orig.isEmpty()) {
			text += QStringLiteral("\n(%1)").arg(autorAndTitleOrig());
		}
		text += QStringLiteral("\n\nЖанр: %1").arg(_genre);
		text += QStringLiteral("\nГод: %1").arg(yearString());
		text += QStringLiteral("\nОценка: %1").arg(_rating);
		return text;
	}

private:
	QString _author_tr;
	QString _author_orig;
	QString _title_tr;
	QString _title_orig;
	QString _genre;
	uint32_t _year = Global::undefined_value;
	uint32_t _rating = Global::undefined_value;
};

} // namespace Books
