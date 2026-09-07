#pragma once

namespace Player
{

enum class LibraryViewModes
{
	Unknown,
	Library,
	Libraries,
};

enum class DataListViewModes
{
	ByArtists,
	ByAlbums,
	ByTracks,
	ByBestTracks,
	ByGenres,
	ByFormats,
	ByYears,
	Summary,
	HistoryArtists,
	HistoryAlbums,
	HistoryTracks,
};

enum class ChartViewModes
{
	ByPlayCounts,
	ByArtists,
	ByYears,
	ByDecades,
	HistoryPlayCounts,
	HistoryArtists,
	HistoryAlbums,
	HistoryTracks,
};

inline const char settings_group_name[] = "player";

inline const char artist_title_misc[] = "Разное";

} // namespace Player
