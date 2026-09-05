#pragma once

#include "PlayerAlbum.h"

#include <common/Global.h>
#include <common/Helper.h>

#include <QString>

#include <map>

namespace Player
{

class Artist
{
	Q_DECLARE_TR_FUNCTIONS(Artist)
public:
	Artist() = default;
	Artist(const QString& title) : _title(title) {}

	using AlbumsContainer = std::map<QString, Album>;

	AlbumsContainer::iterator begin() noexcept
	{ return _albums.begin(); }
	AlbumsContainer::const_iterator begin() const noexcept
	{ return _albums.begin(); }

	AlbumsContainer::iterator end() noexcept
	{ return _albums.end(); }
	AlbumsContainer::const_iterator end() const noexcept
	{ return _albums.end(); }

	Album& operator[](const QString& title)
	{ return _albums[title]; }

	template<typename T>
	inline void setTitle(T&& title)
	{ _title = std::forward<T>(title); }
	inline QString title() const
	{ return _title; }
	inline bool isTitleEmpty() const noexcept
	{ return _title.isEmpty(); }

	QString genre() const
	{
		if (_albums.empty()) { return QString(); }
		QString genre_first = _albums.begin()->second.genre();
		QString genre_last = _albums.rbegin()->second.genre();
		return (genre_first == genre_last) ? genre_first : QString("[Разные]");
	}

	auto minYear() const
	{
		auto min_year = Global::undefined_value;
		for (const auto& item : _albums) { Helper::checkMin(item.second.minYear(), &min_year); }
		return min_year;
	}
	auto maxYear() const
	{
		auto max_year = Global::undefined_value;
		for (const auto& item : _albums) { Helper::checkMax(item.second.maxYear(), &max_year); }
		return max_year;
	}
	QString yearString() const
	{ return Helper::yearString(minYear(), maxYear()); }

	uint32_t playCount() const
	{
		uint32_t sum = 0;
		for (const auto& item : _albums) { sum += item.second.playCount(); }
		return sum;
	}

	uint64_t size() const
	{
		auto sum = uint64_t(0);
		for (const auto& item : _albums) { sum += item.second.size(); }
		return sum;
	}

	uint64_t time() const
	{
		auto sum = uint64_t(0);
		for (const auto& item : _albums) { sum += item.second.time(); }
		return sum;
	}

	auto albumsCount() const
	{ return _albums.size(); }

	auto tracksCount() const
	{
		size_t sum = 0;
		for (const auto& item : _albums) { sum += item.second.tracksCount(); }
		return sum;
	}

	QString summaryString() const
	{
		QString text;
		text += Helper::htmlTableStart();
		text += Helper::htmlTableRow(tr("Группа"), _title);
		text += Helper::htmlTableRow(tr("Год"), yearString());
		text += Helper::htmlTableRow(tr("Альбомов"), QString::number(albumsCount()));
		text += Helper::htmlTableRow(tr("Треков"), QString::number(tracksCount()));
		text += Helper::htmlTableRow(tr("Прослушиваний"), QString::number(playCount()));
		text += Helper::htmlTableRow(tr("Жанр"), genre());
		text += Helper::htmlTableRow(tr("Длина"), Helper::timeString(time()));
		text += Helper::htmlTableRow(tr("Размер"), Helper::sizeString(size()));
		text += Helper::htmlTableEnd();
		return text;
	}

private:
	QString _title;
	AlbumsContainer _albums;
};

} // namespace Player
