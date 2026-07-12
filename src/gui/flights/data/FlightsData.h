#pragma once

#include <common/Global.h>
#include <common/Helper.h>

#include <gui/base/data/BaseData.h>

#include <vector>

namespace Flights
{

class Data : public Base::Data
{
public:
	struct FlightPoint
	{
		QString country;
		QString city;
		QString airport;

		inline bool operator==(const FlightPoint& other) const noexcept
		{
			return	(country == other.country) &&
					(city == other.city) &&
					(airport == other.airport);
		}
	};
	using FlightPoints = std::vector<FlightPoint>;

public:
	Data() = default;

	void clear()
	{ *this = Data(); }

	inline QString id() const override
	{ return _date; }

	template<typename T>
	inline void setDate(T&& date)
	{ _date = std::forward<T>(date); }
	inline QString date() const
	{ return _date; }

	inline uint32_t year() const
	{ return (_date.size() >= 4) ? _date.first(4).toUInt() : Global::undefined_value; }

	template<typename T>
	inline void setPoints(T&& points)
	{ _points = std::forward<T>(points); }
	inline void addPointFromString(const QString& str, const QString& delimiter = ", ")
	{
		if (str.isEmpty()) { return; }
		auto values = str.split(delimiter);
		FlightPoint point;
		if (values.size() >= 1) { point.country = values[0]; }
		if (values.size() >= 2) { point.city = values[1]; }
		if (values.size() >= 3) { point.airport = values[2]; }
		_points.push_back(point);
	}
	inline size_t pointsNum() const
	{ return _points.size(); }
	inline FlightPoints points() const
	{ return _points; }
	inline FlightPoint point(size_t index) const
	{ return _points[index]; }
	inline QString pointToString(size_t index, const QString& delimiter = ", ") const
	{
		if (index < _points.size()) {
			return	_points[index].country + delimiter +
					_points[index].city + delimiter +
					_points[index].airport;
		}
		return QString();
	}
	inline QString pointsToString(const QString& delimiter_points = "  →  ",
								  const QString& delimiter = ", ") const
	{
		QString str;
		for (size_t i = 0; i < _points.size(); ++i) {
			str += pointToString(i, delimiter);
			if (i != (_points.size() - 1)) {
				str += delimiter_points;
			}
		}
		return str;
	}

	inline uint32_t flightsNum() const
	{ return _points.empty() ? 0 : (_points.size() - 1); }

	inline QString country(size_t index) const
	{ return _points[index].country; }
	inline QStringList countries() const
	{
		QStringList list_of_countries;
		for (const auto& point : _points) {
			if (!list_of_countries.contains(point.country)) {
				list_of_countries.append(point.country);
			}
		}
		return list_of_countries;
	}

	inline QString city(size_t index) const
	{ return _points[index].city; }
	inline QStringList cities() const
	{
		QStringList list_of_cities;
		for (const auto& point : _points) {
			QString city_str = point.country + ", " + point.city;
			if (!list_of_cities.contains(city_str)) {
				list_of_cities.append(city_str);
			}
		}
		return list_of_cities;
	}

	inline QString airport(size_t index) const
	{ return _points[index].airport; }
	inline QStringList airports() const
	{
		QStringList list_of_airports;
		for (const auto& point : _points) {
			QString airport_str = point.country + ", " + point.city + ", " + point.airport;
			if (!list_of_airports.contains(airport_str)) {
				list_of_airports.append(airport_str);
			}
		}
		return list_of_airports;
	}

	inline bool operator==(const Data& other) const noexcept
	{
		return	(_date == other.date()) &&
				(_points == other.points());
	}

private:
	QString _date; // YYYY.MM.DD
	FlightPoints _points;
};

} // namespace Flights
