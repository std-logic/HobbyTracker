#pragma once

#include <common/Global.h>
#include <common/Helper.h>

#include <gui/base/data/BaseData.h>

namespace Movies
{

class Data : public Base::Data
{
	Q_DECLARE_TR_FUNCTIONS(Data)
public:
	Data() = default;

	void clear()
	{ *this = Data(); }

	inline QString id() const override
	{ return _view_date + _title_tr + QString::number(_year); }

	template<typename T>
	inline void setViewDate(T&& view_date)
	{ _view_date = std::forward<T>(view_date); }
	inline QString viewDate() const
	{ return _view_date; }
	inline uint32_t viewYear() const
	{ return (_view_date.size() >= 4) ? _view_date.first(4).toUInt() : Global::undefined_value; }

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

	template<typename T>
	inline void setKind(T&& kind)
	{ _kind = std::forward<T>(kind); }
	inline QString kind() const
	{ return _kind; }

	template<typename T>
	inline void setGenres(T&& genres)
	{ _genres = std::forward<T>(genres); }
	inline void setGenresFromString(const QString& str, const QString& delimiter = ", ")
	{ _genres = str.split(delimiter, Qt::SkipEmptyParts); }
	inline QStringList genres() const
	{ return _genres; }
	inline QString genresToString(const QString& delimiter = ", ") const
	{ return Helper::stringListToString(_genres, delimiter); }

	template<typename T>
	inline void setCountries(T&& countries)
	{ _countries = std::forward<T>(countries); }
	inline void setCountriesFromString(const QString& str, const QString& delimiter = ", ")
	{ _countries = str.split(delimiter, Qt::SkipEmptyParts); }
	inline QStringList countries() const
	{ return _countries; }
	inline QString countriesToString(const QString& delimiter = ", ") const
	{ return Helper::stringListToString(_countries, delimiter); }

	template<typename T>
	inline void setDirectors(T&& directors)
	{ _directors = std::forward<T>(directors); }
	inline void setDirectorsFromString(const QString& str, const QString& delimiter = ", ")
	{ _directors = str.split(delimiter, Qt::SkipEmptyParts); }
	inline QStringList directors() const
	{ return _directors; }
	inline QString directorsToString(const QString& delimiter = ", ") const
	{ return Helper::stringListToString(_directors, delimiter); }

	template<typename T>
	inline void setWriters(T&& writers)
	{ _writers = std::forward<T>(writers); }
	inline void setWritersFromString(const QString& str, const QString& delimiter = ", ")
	{ _writers = str.split(delimiter, Qt::SkipEmptyParts); }
	inline QStringList writers() const
	{ return _writers; }
	inline QString writersToString(const QString& delimiter = ", ") const
	{ return Helper::stringListToString(_writers, delimiter); }

	template<typename T>
	inline void setActors(T&& actors)
	{ _actors = std::forward<T>(actors); }
	inline void setActorsFromString(const QString& str, const QString& delimiter = ", ")
	{ _actors = str.split(delimiter, Qt::SkipEmptyParts); }
	inline QStringList actors() const
	{ return _actors; }
	inline QString actorsToString(const QString& delimiter = ", ") const
	{ return Helper::stringListToString(_actors, delimiter); }

	inline void setTime(uint32_t time)
	{ _time = time; }
	inline uint32_t time() const
	{ return _time; }
	QString timeString() const
	{ return Helper::timeString(_time * 60); }

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

	inline void setFavorite(bool favorite)
	{ _favorite = favorite; }
	inline bool isFavorite() const
	{ return _favorite; }

	QString summaryString() const
	{
		QString text;
		text += title();
		text += tr("\n\nТип: ") + _kind;
		text += tr("\nЖанры: ") + genresToString();
		text += tr("\nСтраны: ") + countriesToString();
		text += tr("\nРежиссёр: ") + directorsToString();
		text += tr("\nСценарист: ") + writersToString();
		text += tr("\nАктёры: ") + actorsToString();
		text += tr("\nДлительность: ") + timeString();
		text += tr("\nГод: ") + yearString();
		text += tr("\nОценка: %1 (%2)").arg(_rating).arg(_view_date);
		return text;
	}

	inline bool operator==(const Data& other) const noexcept
	{
		return	(_view_date == other.viewDate()) &&
				(_title_tr == other.titleTr()) &&
				(_title_orig == other.titleOrig()) &&
				(_kind == other.kind()) &&
				(_genres == other.genres()) &&
				(_countries == other.countries()) &&
				(_directors == other.directors()) &&
				(_writers == other.writers()) &&
				(_actors == other.actors()) &&
				(_time == other.time()) &&
				(_year == other.year()) &&
				(_rating == other.rating()) &&
				(_favorite == other.isFavorite());
	}

private:
	QString _view_date; // YYYY.MM.DD
	QString _title_tr;
	QString _title_orig;
	QString _kind;
	QStringList _genres;
	QStringList _countries;
	QStringList _directors;
	QStringList _writers;
	QStringList _actors;
	uint32_t _time = 0; // minutes
	uint32_t _year = Global::undefined_value;
	uint32_t _rating = Global::undefined_value;
	bool _favorite = false;
};

} // namespace Movies
