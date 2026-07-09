#pragma once

#include <common/Global.h>
#include <common/Helper.h>

#include <gui/base/data/BaseData.h>

namespace Bike
{

class Data : public Base::Data
{
public:
	Data() = default;

	void clear()
	{ *this = Data(); }

	inline QString id() const override
	{ return QString::number(_year); }

	inline void setYear(uint32_t year)
	{ _year = year; }
	inline uint32_t year() const
	{ return _year; }
	QString yearString() const
	{ return Helper::yearString(_year); }

	inline void setTime(uint32_t time)
	{ _time = time; }
	inline uint32_t time() const
	{ return _time; }

	inline void setDist(uint32_t dist)
	{ _dist = dist; }
	inline uint32_t dist() const
	{ return _dist; }

	inline bool operator==(const Data& other) const noexcept
	{
		return	(_year == other.year()) &&
				(_time == other.time()) &&
				(_dist == other.dist());
	}

private:
	uint32_t _year = Global::undefined_value;
	uint32_t _time = 0; // hours
	uint32_t _dist = 0; // km
};

} // namespace Bike
