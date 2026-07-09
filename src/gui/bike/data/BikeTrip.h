#pragma once

#include <common/Global.h>
#include <common/Helper.h>

#include <gui/base/data/BaseData.h>

namespace Bike
{

class Trip : public Base::Data
{
public:
	Trip() = default;

	void clear()
	{ *this = Trip(); }

	inline QString id() const override
	{ return _date_start; }

	template<typename T>
	inline void setDateStart(T&& date_start)
	{ _date_start = std::forward<T>(date_start); }
	inline QString dateStart() const
	{ return _date_start; }

	template<typename T>
	inline void setDateEnd(T&& date_end)
	{ _date_end = std::forward<T>(date_end); }
	inline QString dateEnd() const
	{ return _date_end; }

	inline QString dates() const
	{ return QStringLiteral("%1-%2").arg(_date_start, _date_end.mid(5)); }

	inline uint32_t year() const
	{
		return (_date_start.size() >= 4) ?
				_date_start.first(4).toUInt() :
				Global::undefined_value;
	}

	inline void setDist(uint32_t dist)
	{ _dist = dist; }
	inline uint32_t dist() const
	{ return _dist; }

	inline void setTime(uint32_t time)
	{ _time = time; }
	inline uint32_t time() const
	{ return _time; }

	template<typename T>
	inline void setCountries(T&& countries)
	{ _countries = std::forward<T>(countries); }
	inline void setCountriesFromString(const QString& countries, const QString& delimiter = QStringLiteral(", "))
	{ _countries = countries.split(delimiter); }
	inline QStringList countries() const
	{ return _countries; }
	inline QString countriesToString(const QString& delimiter = QStringLiteral(", ")) const
	{ return Helper::stringListToString(_countries, delimiter); }

	template<typename T>
	inline void setPlaces(T&& places)
	{ _places = std::forward<T>(places); }
	inline void setPlacesFromString(const QString& places, const QString& delimiter = QStringLiteral(", "))
	{ _places = places.split(delimiter); }
	inline QStringList places() const
	{ return _places; }
	inline QString placesToString(const QString& delimiter = QStringLiteral(", ")) const
	{ return Helper::stringListToString(_places, delimiter); }

	inline bool operator==(const Trip& other) const noexcept
	{
		return	(_date_start == other.dateStart()) &&
				(_date_end == other.dateEnd()) &&
				(_dist == other.dist()) &&
				(_time == other.time()) &&
				(_countries == other.countries()) &&
				(_places == other.places());
	}

private:
	QString _date_start; // YYYY.MM.DD
	QString _date_end; // YYYY.MM.DD
	uint32_t _dist = 0; // km
	uint32_t _time = 0; // nights
	QStringList _countries;
	QStringList _places;
};

} // namespace Bike
