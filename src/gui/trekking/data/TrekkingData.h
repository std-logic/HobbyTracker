#pragma once

#include <common/Global.h>
#include <common/Helper.h>

#include <gui/base/data/BaseData.h>

namespace Trekking
{

class Data : public Base::Data
{
	Q_DECLARE_TR_FUNCTIONS(Data)
public:
	Data() = default;

	void clear()
	{ *this = Data(); }

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
	{ return QStringLiteral("%1 - %2").arg(_date_start, _date_end.mid(5)); }

	inline uint32_t year() const
	{ return (_date_start.size() >= 4) ? _date_start.first(4).toUInt() : Global::undefined_value; }

	inline void setTime(uint32_t time)
	{ _time = time; }
	inline uint32_t time() const
	{ return _time; }

	inline void setDist(uint32_t dist)
	{ _dist = dist; }
	inline uint32_t dist() const
	{ return _dist; }

	inline void setPeak(uint32_t peak)
	{ _peak = peak; }
	inline uint32_t peak() const
	{ return _peak; }

	template<typename T>
	inline void setKind(T&& kind)
	{ _kind = std::forward<T>(kind); }
	inline QString kind() const
	{ return _kind; }

	template<typename T>
	inline void setCountries(T&& countries)
	{ _countries = std::forward<T>(countries); }
	inline void setCountriesFromString(const QString& str, const QString& delimiter = ", ")
	{ _countries = str.split(delimiter, Qt::SkipEmptyParts); }
	inline QStringList countries() const
	{ return _countries; }
	inline QString countriesToString(const QString& delimiter = ", ") const
	{ return _countries.join(delimiter); }

	template<typename T>
	inline void setPlaces(T&& places)
	{ _places = std::forward<T>(places); }
	inline QString places() const
	{ return _places; }

	QString summaryString() const
	{
		QString text;
		text += Helper::htmlTableStart();
		text += Helper::htmlTableRow(tr("Старт"), _date_start);
		text += Helper::htmlTableRow(tr("Финиш"), _date_end);
		text += Helper::htmlTableRow(tr("Ночёвок"), QString::number(_time));
		text += Helper::htmlTableRow(tr("Расстояние"), tr("%1 км").arg(_dist));
		text += Helper::htmlTableRow(tr("Высшая точка"), tr("%1 м").arg(_peak));
		text += Helper::htmlTableRow(tr("Тип"), _kind);
		auto countries_head = (_countries.size() > 1) ? tr("Страны") : tr("Страна");
		text += Helper::htmlTableRow(countries_head, countriesToString());
		text += Helper::htmlTableRow(tr("Место"), _places);
		text += Helper::htmlTableEnd();
		return text;
	}

	inline bool operator==(const Data& other) const noexcept
	{
		return	(_date_start == other.dateStart()) &&
				(_date_end == other.dateEnd()) &&
				(_time == other.time()) &&
				(_dist == other.dist()) &&
				(_peak == other.peak()) &&
				(_kind == other.kind()) &&
				(_countries == other.countries()) &&
				(_places == other.places());
	}

private:
	QString _date_start; // YYYY.MM.DD
	QString _date_end; // YYYY.MM.DD
	uint32_t _time = 0; // nights
	uint32_t _dist = 0; // km
	uint32_t _peak = 0; // m
	QString _kind;
	QStringList _countries;
	QString _places;
};

} // namespace Trekking
