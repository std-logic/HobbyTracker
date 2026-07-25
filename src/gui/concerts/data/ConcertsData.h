#pragma once

#include "../common/ConcertsCommon.h"

#include <common/Global.h>
#include <common/Helper.h>

#include <gui/base/data/BaseData.h>

namespace Concerts
{

class Data : public Base::Data
{
public:
	Data() = default;

	void clear()
	{ *this = Data(); }

	inline QString id() const override
	{ return _date + _place; }

	template<typename T>
	inline void setDate(T&& date)
	{ _date = std::forward<T>(date); }
	inline QString date() const
	{ return _date; }

	inline uint32_t year() const
	{ return (_date.size() >= 4) ? _date.first(4).toUInt() : Global::undefined_value; }

	template<typename T>
	inline void setArtists(T&& artists)
	{ _artists = std::forward<T>(artists); }
	inline void setArtistsFromString(const QString& str, const QString& delimiter = ", ")
	{ _artists = str.split(delimiter); }
	inline QStringList artists() const
	{ return _artists; }
	inline QString artistsToString(const QString& delimiter = ", ") const
	{ return Helper::stringListToString(_artists, delimiter); }

	template<typename T>
	inline void setKinds(T&& kinds)
	{ _kinds = std::forward<T>(kinds); }
	inline void setKindsFromString(const QString& str, const QString& delimiter = ", ")
	{ _kinds = str.split(delimiter); }
	inline QStringList kinds() const
	{ return _kinds; }
	inline QString kindsToString(const QString& delimiter = ", ") const
	{ return Helper::stringListToString(_kinds, delimiter); }

	template<typename T>
	inline void setCountry(T&& country)
	{ _country = std::forward<T>(country); }
	inline QString country() const
	{ return _country; }

	template<typename T>
	inline void setCity(T&& city)
	{ _city = std::forward<T>(city); }
	inline QString city() const
	{ return _city; }

	template<typename T>
	inline void setPlace(T&& place)
	{ _place = std::forward<T>(place); }
	inline QString place() const
	{ return _place; }

	inline bool operator==(const Data& other) const noexcept
	{
		return	(_date == other.date()) &&
				(_artists == other.artists()) &&
				(_kinds == other.kinds()) &&
				(_country == other.country()) &&
				(_city == other.city()) &&
				(_place == other.place());
	}

private:
	QString _date; // YYYY.MM.DD
	QStringList _artists;
	QStringList _kinds;
	QString _country;
	QString _city;
	QString _place;
};

} // namespace Concerts
