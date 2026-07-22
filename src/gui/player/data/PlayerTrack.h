#pragma once

#include <common/Global.h>
#include <common/Helper.h>

#include <QString>

namespace Player
{

class Track
{
public:
	Track() = default;
	Track(const QString& title) : _title(title) {}

	inline bool operator==(const Track& track) const noexcept
	{
		return	(_title == track.title()) &&
				(_album == track.album()) &&
				(_artist == track.artist());
	}

	Track& operator-=(const Track& track) noexcept
	{
		if (_play_count >= track._play_count) {
			_play_count -= track._play_count;
		} else {
			_play_count = 0;
		}
		return *this;
	}

	template<typename T>
	inline void setTitle(T&& title)
	{ _title = std::forward<T>(title); }
	inline QString title() const
	{ return _title; }
	inline QString titleWithTrackNumber() const
	{
		return	(_track_number == Global::undefined_value) ? _title :
				QStringLiteral("%1. %2").arg(_track_number, 2, 10, QChar('0')).arg(_title);
	}

	template<typename T>
	inline void setAlbum(T&& album)
	{ _album = std::forward<T>(album); }
	inline QString album() const
	{ return _album; }

	template<typename T>
	inline void setArtist(T&& artist)
	{ _artist = std::forward<T>(artist); }
	inline QString artist() const
	{ return _artist; }

	template<typename T>
	inline void setGenre(T&& genre)
	{ _genre = std::forward<T>(genre); }
	inline QString genre() const
	{ return _genre; }

	template<typename T>
	inline void setComposer(T&& composer)
	{ _composer = std::forward<T>(composer); }
	inline QString composer() const
	{ return _composer; }

	template<typename T>
	inline void setFormat(T&& format)
	{ _format = std::forward<T>(format); }
	inline QString format() const
	{ return _format; }

	template<typename T>
	inline void setPublisher(T&& publisher)
	{ _publisher = std::forward<T>(publisher); }
	inline QString publisher() const
	{ return _publisher; }

	template<typename T>
	inline void setComments(T&& comments)
	{ _comments = std::forward<T>(comments); }
	inline QString comments() const
	{ return _comments; }

	inline void setTrackNumer(uint32_t track_number)
	{ _track_number = track_number; }
	inline uint32_t trackNumber() const
	{ return _track_number; }

	inline void setYear(uint32_t year)
	{ _year = year; }
	inline uint32_t year() const
	{ return _year; }
	inline QString yearString() const
	{ return Helper::yearString(_year); }

	inline void setPlayCount(uint32_t play_count)
	{ _play_count = play_count; }
	inline uint32_t playCount() const
	{ return _play_count; }

	inline void setSize(uint32_t size)
	{ _size = size; }
	inline uint64_t size() const
	{ return _size; }

	inline void setTime(uint32_t time)
	{ _time = time; }
	inline uint32_t time() const
	{ return _time; }

	inline void setBitrate(uint32_t bitrate)
	{ _bitrate = bitrate; }
	inline uint32_t bitrate() const
	{ return _bitrate; }

	QString summaryString() const
	{
		QString text;
		text += QString("Трек: %1").arg(_title);
		if (_year != Global::undefined_value) { text += QString("\nГод: %1").arg(yearString()); }
		text += QString("\nПрослушиваний: %1").arg(_play_count);
		text += QString("\nЖанр: %1").arg(_genre);
		text += QString("\nДлина: %1").arg(Helper::timeString(_time));
		text += QString("\nРазмер: %1").arg(Helper::sizeString(_size));
		text += QString("\nБитрейт: %1 кбит/с (%2)").arg(_bitrate).arg(_format);
		if (!_composer.isEmpty()) { text += QString("\nКомпозитор: %1").arg(_composer); }
		if (!_publisher.isEmpty()) { text += QString("\nИздатель: %1").arg(_publisher); }
		if (!_comments.isEmpty()) { text += QString("\n\n%1").arg(_comments); }
		return text;
	}

private:
	QString _title;
	QString _album;
	QString _artist;
	QString _genre;
	QString _composer;
	QString _format;
	QString _publisher;
	QString _comments;
	uint32_t _track_number = Global::undefined_value;
	uint32_t _year = Global::undefined_value;
	uint32_t _play_count = 0;
	uint32_t _size = 0;
	uint32_t _time = 0;
	uint32_t _bitrate = 0;
};

} // namespace Player
