#pragma once

#include <common/Global.h>
#include <common/Helper.h>

#include <gui/base/data/BaseData.h>

namespace Coins
{

class Data : public Base::Data
{
	Q_DECLARE_TR_FUNCTIONS(Data)
public:
	Data() = default;

	void clear()
	{ *this = Data(); }

	inline QString id() const override
	{ return _country + _value + _number + QString::number(_year); }

	template<typename T>
	inline void setCountry(T&& country)
	{ _country = std::forward<T>(country); }
	inline QString country() const
	{ return _country; }

	template<typename T>
	inline void setPeriod(T&& period)
	{ _period = std::forward<T>(period); }
	inline QString period() const
	{ return _period; }

	inline QString countryPeriod() const
	{ return _country + ", " + _period; }
	inline QString countryPeriod(const QString& country_synonym) const
	{ return country_synonym + ", " + _period; }

	template<typename T>
	inline void setValue(T&& value)
	{ _value = std::forward<T>(value); }
	inline QString value() const
	{ return _value; }

	template<typename T>
	inline void setVersion(T&& version)
	{ _version = std::forward<T>(version); }
	inline QString version() const
	{ return _version; }

	template<typename T>
	inline void setCurrency(T&& currency)
	{ _currency = std::forward<T>(currency); }
	inline QString currency() const
	{ return _currency; }

	template<typename T>
	inline void setTitle(T&& title)
	{ _title = std::forward<T>(title); }
	inline QString title() const
	{ return _title; }

	template<typename T>
	inline void setState(T&& state)
	{ _state = std::forward<T>(state); }
	inline QString state() const
	{ return _state; }

	template<typename T>
	inline void setNumber(T&& number)
	{ _number = std::forward<T>(number); }
	inline QString number() const
	{ return _number; }

	template<typename T>
	inline void setDiameter(T&& diameter)
	{ _diameter = std::forward<T>(diameter); }
	inline QString diameter() const
	{ return _diameter; }
	inline uint32_t diameterRounded() const
	{ return qRound(_diameter.toDouble()); }

	inline void setYear(uint32_t year)
	{ _year = year;}
	inline uint32_t year() const
	{ return _year; }
	QString yearString() const
	{ return Helper::yearString(_year); }

	QString summaryString() const
	{
		QString text;
		text += tr("Страна: ") + _country;
		text += tr("\nПериод: ") + _period;
		text += tr("\nВалюта: ") + _currency;
		text += tr("\nНоминал: ") + _value;
		if (!_title.isEmpty()) { text += tr("\nНазвание: ") + _title; }
		text += tr("\nДиаметр: ") + _diameter;
		text += tr("\nНомер: ") + _number;
		text += tr("\nГод: ") + yearString();
		if (!_version.isEmpty()) { text += tr("\nРазновидность: ") + _version; }
		if (!_state.isEmpty()) { text += tr("\nСостояние: ") + _state; }
		return text;
	}

	inline bool operator==(const Data& other) const noexcept
	{
		return	(_country == other.country()) &&
				(_period == other.period()) &&
				(_value == other.value()) &&
				(_version == other.version()) &&
				(_currency == other.currency()) &&
				(_title == other.title()) &&
				(_state == other.state()) &&
				(_number == other.number()) &&
				(_diameter == other.diameter()) &&
				(_year == other.year());
	}

private:
	QString _country;
	QString _period;
	QString _value;
	QString _version;
	QString _currency;
	QString _title;
	QString _state;
	QString _number;
	QString _diameter;
	uint32_t _year = Global::undefined_value;
};

} // namespace Coins
