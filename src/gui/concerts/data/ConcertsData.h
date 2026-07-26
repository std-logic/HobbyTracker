#pragma once

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
	{ _artists = str.split(delimiter, Qt::SkipEmptyParts); }
	inline QStringList artists() const
	{ return _artists; }
	inline QString artistsToString(const QString& delimiter = ", ") const
	{ return Helper::stringListToString(_artists, delimiter); }

	template<typename T>
	inline void setDescription(T&& description)
	{ _description = std::forward<T>(description); }
	inline QString description() const
	{ return _description; }

	QString artistsAndDescriptionToString(const QString& delimiter = ", ") const
	{
		QString str;
		if (!_artists.empty()) {
			str = artistsToString(delimiter);
			if (!_description.isEmpty()) { str += " (" + _description + ")"; }
		} else if (!_description.isEmpty()) {
			str = Helper::startWithCapital(_description);
		}
		return str;
	}

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

	inline QString countryCity() const
	{ return _country + ", " + _city; }
	inline QString cityPlace() const
	{ return _city + ", " + _place; }
	inline QString countryCityPlace() const
	{ return _country + ", " + _city + ", " + _place; }

	inline bool operator==(const Data& other) const noexcept
	{
		return	(_date == other.date()) &&
				(_artists == other.artists()) &&
				(_description == other.description()) &&
				(_country == other.country()) &&
				(_city == other.city()) &&
				(_place == other.place());
	}

private:
	QString _date; // YYYY.MM.DD
	QStringList _artists;
	QString _description;
	QString _country;
	QString _city;
	QString _place;
};

} // namespace Concerts
