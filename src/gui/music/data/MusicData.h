#pragma once

#include "../common/MusicCommon.h"

#include <common/Global.h>
#include <common/Helper.h>

#include <gui/base/data/BaseData.h>

namespace Music
{

class Data : public Base::Data
{
	Q_DECLARE_TR_FUNCTIONS(Data)
public:
	Data() = default;

	void clear()
	{ *this = Data(); }

	inline QString id() const override
	{ return _title; }

	template<typename T>
	inline void setTitle(T&& title)
	{ _title = std::forward<T>(title); }
	inline QString title() const
	{ return _title; }

	template<typename T>
	inline void setGenre(T&& genre)
	{ _genre = std::forward<T>(genre); }
	inline QString genre() const
	{ return _genre; }

	template<typename T>
	inline void setCountry(T&& country)
	{ _country = std::forward<T>(country); }
	inline QString country() const
	{ return _country; }

	inline void setYear(uint32_t year)
	{ _year = year; }
	inline uint32_t year() const
	{ return _year; }
	QString yearString() const
	{ return Helper::yearString(_year); }

	inline void setState(States state)
	{ _state = state; }
	inline uint32_t state() const
	{ return static_cast<uint32_t>(_state); }
	inline bool isActive() const
	{ return (_state == States::Active); }
	inline QString stateString() const
	{ return stateString(_state); }
	static inline QString stateString(States state)
	{ return (state == States::Active) ? QStringLiteral("+") : QStringLiteral("−"); }
	inline QString stateStringYesNo() const
	{ return stateStringYesNo(_state); }
	static inline QString stateStringYesNo(States state)
	{ return (state == States::Active) ? tr("Да") : tr("Нет"); }
	inline QColor stateColor() const
	{ return stateColor(_state); }
	static inline QColor stateColor(States state)
	{ return (state == States::Active) ? QColor(180, 245, 190) : QColor(245, 190, 190); }

	inline void setLive(Live live)
	{ _live = live; }
	inline uint32_t live() const
	{ return static_cast<uint32_t>(_live); }
	inline bool isVisited() const
	{ return (_live == Live::Visited); }
	inline QString liveString() const
	{ return liveString(_live); }
	static inline QString liveString(Live live)
	{ return (live == Live::Visited) ? QStringLiteral("+") : QStringLiteral("−"); }
	inline QString liveStringYesNo() const
	{ return liveStringYesNo(_live); }
	static inline QString liveStringYesNo(Live live)
	{ return (live == Live::Visited) ? tr("Да") : tr("Нет"); }
	inline QColor liveColor() const
	{ return liveColor(_live); }
	static inline QColor liveColor(Live live)
	{ return (live == Live::Visited) ? QColor(180, 245, 190) : QColor(245, 190, 190); }

	QString summaryString() const
	{
		QString text;
		text += _title;
		text += tr("\n\nЖанр: %1").arg(_genre);
		text += tr("\nСтрана основания: %1").arg(_country);
		text += tr("\nГод основания: %1").arg(yearString());
		text += tr("\nБыл на концерте: %1").arg(liveStringYesNo());
		text += tr("\nАктивна: %1").arg(stateStringYesNo());
		return text;
	}

	inline bool operator==(const Data& other) const noexcept
	{
		return	(_title == other.title()) &&
				(_genre == other.genre()) &&
				(_country == other.country()) &&
				(_year == other.year()) &&
				(static_cast<uint32_t>(_state) == other.state()) &&
				(static_cast<uint32_t>(_live) == other.live());
	}

private:
	QString _title;
	QString _genre;
	QString _country;
	uint32_t _year = Global::undefined_value;
	States _state = States::Inactive;
	Live _live = Live::Unvisited;
};

} // namespace Music
