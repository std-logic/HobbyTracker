#pragma once

#include "PlayerArtist.h"
#include "../common/PlayerCommon.h"

#include <common/Global.h>
#include <common/Helper.h>

#include <QString>

#include <map>

namespace Player
{

class Library
{
	Q_DECLARE_TR_FUNCTIONS(Library)
public:
	Library() = default;
	Library(const QString& title) : _title(title) {}

	using ArtistsContainer = std::map<QString, Artist>;

	ArtistsContainer::iterator begin() noexcept
	{ return _artists.begin(); }
	ArtistsContainer::const_iterator begin() const noexcept
	{ return _artists.begin(); }

	ArtistsContainer::iterator end() noexcept
	{ return _artists.end(); }
	ArtistsContainer::const_iterator end() const noexcept
	{ return _artists.end(); }

	Artist& operator[](const QString& title)
	{ return _artists[title]; }

	void clear() noexcept
	{ _title.clear(); _artists.clear(); }
	bool empty() const noexcept
	{ return _artists.empty(); }

	template<typename T>
	inline void setTitle(T&& title)
	{ _title = std::forward<T>(title); }
	inline QString title() const
	{ return _title; }
	inline QString titleOnlyDate() const
	{
		QString title_cropped = _title;
		title_cropped.remove(QStringLiteral("winamp_")).remove(QStringLiteral(".xml"));
		return title_cropped;
	}
	inline bool isTitleEmpty() const noexcept
	{ return _title.isEmpty(); }

	auto minYear() const
	{
		auto min_year = Global::undefined_value;
		for (const auto& item : _artists) { Helper::checkMin(item.second.minYear(), &min_year); }
		return min_year;
	}
	auto maxYear() const
	{
		auto max_year = Global::undefined_value;
		for (const auto& item : _artists) { Helper::checkMax(item.second.maxYear(), &max_year); }
		return max_year;
	}
	QString yearString() const
	{ return Helper::yearString(minYear(), maxYear()); }

	uint32_t playCount() const
	{
		uint32_t sum = 0;
		for (const auto& item : _artists) { sum += item.second.playCount(); }
		return sum;
	}

	uint64_t size() const
	{
		auto sum = uint64_t(0);
		for (const auto& item : _artists) { sum += item.second.size(); }
		return sum;
	}

	uint64_t time() const
	{
		auto sum = uint64_t(0);
		for (const auto& item : _artists) { sum += item.second.time(); }
		return sum;
	}

	auto artistsCount(bool expand_misc = false) const
	{
		size_t sum = _artists.size();
		if (expand_misc) {
			for (const auto& [artist_title, artist] : _artists) {
				if (artist_title == artist_title_misc) {
					sum += artist.albumsCount() - 1;
					break;
				}
			}
		}
		return sum;
	}

	auto albumsCount() const
	{
		size_t sum = 0;
		for (const auto& item : _artists) { sum += item.second.albumsCount(); }
		return sum;
	}

	auto tracksCount() const
	{
		size_t sum = 0;
		for (const auto& item : _artists) { sum += item.second.tracksCount(); }
		return sum;
	}

	using TopArtistsData = std::pair<const Artist*, uint32_t>;
	std::vector<TopArtistsData> topArtists(int top_size) const;

	using TopAlbumsData = std::pair<const Album*, uint32_t>;
	std::vector<TopAlbumsData> topAlbums(int top_size) const;

	using TopTracksData = std::pair<const Track*, uint32_t>;
	std::vector<TopTracksData> topTracks(int top_size) const;

	std::tuple<int, int, int> playedCount() const;

	using GenresData = std::map<QString, Library>;
	GenresData genres() const;

	using FormatsData = std::map<QString, Library>;
	FormatsData formats() const;

	using YearsData = std::map<QString, Library>;
	YearsData years() const;

	struct Summary
	{
		QString title;
		uint32_t artists_num = 0;
		uint32_t albums_num = 0;
		uint32_t tracks_num = 0;
		uint32_t play_count = 0;
		uint32_t genres_num = 0;
		uint32_t min_year = Global::undefined_value;
		uint32_t max_year = Global::undefined_value;
	};
	Summary summary(bool expand_misc = false) const;
	QString summaryString(bool expand_misc = false) const;

private:
	QString _title;
	ArtistsContainer _artists;
};

} // namespace Player
