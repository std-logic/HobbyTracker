#pragma once

#include <common/Global.h>
#include <common/Helper.h>

#include <gui/base/data/BaseData.h>

namespace Games
{

class Data : public Base::Data
{
public:
	Data() = default;

	void clear()
	{ *this = Data(); }

	inline QString id() const override
	{ return title() + yearString(); }

	template<typename T>
	inline void setSeries(T&& series)
	{ _series = std::forward<T>(series); }
	inline QString series() const
	{ return _series; }

	template<typename T>
	inline void setTitle(T&& title)
	{ _title = std::forward<T>(title); }
	inline QString title() const
	{ return _title; }

	template<typename T>
	inline void setDeveloper(T&& developer)
	{ _developer = std::forward<T>(developer); }
	inline QString developer() const
	{ return _developer; }

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
		text += _title;
		text += QStringLiteral("\n\nРазработчик: %1").arg(_developer);
		text += QStringLiteral("\nЖанр: %1").arg(_genre);
		text += QStringLiteral("\nГод: %1").arg(yearString());
		text += QStringLiteral("\nОценка: %1").arg(_rating);
		return text;
	}

	inline bool operator==(const Data& other) const noexcept
	{
		return	(_series == other.series()) &&
				(_title == other.title()) &&
				(_developer == other.developer()) &&
				(_genre == other.genre()) &&
				(_year == other.year()) &&
				(_rating == other.rating());
	}

private:
	QString _series;
	QString _title;
	QString _developer;
	QString _genre;
	uint32_t _year = Global::undefined_value;
	uint32_t _rating = Global::undefined_value;
};

} // namespace Games
