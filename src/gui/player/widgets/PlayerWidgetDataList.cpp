#include "PlayerWidgetDataList.h"
#include "../common/PlayerCommon.h"
#include "../data/PlayerLibrary.h"

#include <gui/base/widgets/BaseWidgetTreeItem.h>

Player::WidgetDataList::WidgetDataList(QWidget* parent)
	: Base::WidgetTree{parent}
{
}

void Player::WidgetDataList::update(const Library& library)
{
	clear();
	if (library.empty()) { return; }
	setRootIsDecorated(static_cast<DataListViewModes>(_view_mode) != DataListViewModes::ByTracks);
	switch (static_cast<DataListViewModes>(_view_mode)) {
		case DataListViewModes::ByArtists:		showByArtists(library);			break;
		case DataListViewModes::ByAlbums:		showByAlbums(library);			break;
		case DataListViewModes::ByTracks:		showByTracks(library);			break;
		case DataListViewModes::ByBestTracks:	showByBestTracks(library);		break;
		case DataListViewModes::ByGenres:		showByGenres(library);			break;
		case DataListViewModes::ByFormats:		showByFormats(library);			break;
		case DataListViewModes::Summary:		showSummary(library);			break;
		default: return;
	}
}

void Player::WidgetDataList::update(const std::vector<Library>& libraries)
{
	clear();
	if (libraries.empty()) { return; }
	setRootIsDecorated(static_cast<DataListViewModes>(_view_mode) != DataListViewModes::ByTracks);
	switch (static_cast<DataListViewModes>(_view_mode)) {
		case DataListViewModes::HistoryArtists:	showHistoryArtists(libraries);	break;
		case DataListViewModes::HistoryAlbums:	showHistoryAlbums(libraries);	break;
		case DataListViewModes::HistoryTracks:	showHistoryTracks(libraries);	break;
		default: return;
	}
}

void Player::WidgetDataList::showByArtists(const Library& library)
{
	enum Columns {CLMN_TITLE, CLMN_YEAR, CLMN_ALBUMS, CLMN_TRACKS, CLMN_PLAY_COUNT};
	initColumns({tr("Группа / Альбом / Трек"), tr("Год"), tr("Альбомов"),
				 tr("Треков"), tr("Прослушиваний")},
				{WIDTH_TITLE, WIDTH_YEAR, WIDTH_ALBUMS, WIDTH_TRACKS, WIDTH_PLAY_COUNT});
	initSorting(CLMN_TITLE);

	for (const auto& [artist_title, artist] : library) {
		auto item_artist = new Base::WidgetTreeItem(this, Global::Colors::tree_level_2);
		item_artist->setText(CLMN_TITLE, artist_title);
		item_artist->setToolTip(CLMN_TITLE, artist.summaryString());
		item_artist->setText(CLMN_YEAR, artist.yearString());
		item_artist->setNumb(CLMN_ALBUMS, artist.albumsCount());
		item_artist->setNumb(CLMN_TRACKS, artist.tracksCount());
		item_artist->setNumb(CLMN_PLAY_COUNT, artist.playCount());

		for (const auto& [album_title, album] : artist) {
			auto item_album = new Base::WidgetTreeItem(item_artist, Global::Colors::tree_level_1);
			item_album->setText(CLMN_TITLE, album_title);
			item_album->setToolTip(CLMN_TITLE, album.summaryString());
			item_album->setText(CLMN_YEAR, album.yearString());
			item_album->setNumb(CLMN_TRACKS, album.tracksCount());
			item_album->setNumb(CLMN_PLAY_COUNT, album.playCount());

			for (const auto& track : album) {
				auto item_track = new Base::WidgetTreeItem(item_album);
				item_track->setText(CLMN_TITLE, track.titleWithTrackNumber());
				item_track->setToolTip(CLMN_TITLE, track.summaryString());
				item_track->setText(CLMN_YEAR, track.yearString());
				item_track->setNumb(CLMN_PLAY_COUNT, track.playCount());
			}
		}
	}
}

void Player::WidgetDataList::showByAlbums(const Library& library)
{
	enum Columns {CLMN_TITLE, CLMN_YEAR, CLMN_TRACKS, CLMN_PLAY_COUNT};
	initColumns({tr("Альбом / Трек"), tr("Год"), tr("Треков"), tr("Прослушиваний")},
				{WIDTH_TITLE, WIDTH_YEAR, WIDTH_TRACKS, WIDTH_PLAY_COUNT});
	initSorting(CLMN_TITLE);

	for (const auto& [artist_title, artist] : library) {
		for (const auto& [album_title, album] : artist) {
			auto item_album = new Base::WidgetTreeItem(this, Global::Colors::tree_level_1);
			item_album->setText(CLMN_TITLE, QStringLiteral("[%1] %2")
					.arg(artist_title, album_title));
			item_album->setToolTip(CLMN_TITLE, album.summaryString());
			item_album->setText(CLMN_YEAR, album.yearString());
			item_album->setNumb(CLMN_TRACKS, album.tracksCount());
			item_album->setNumb(CLMN_PLAY_COUNT, album.playCount());

			for (const auto& track : album) {
				auto item_track = new Base::WidgetTreeItem(item_album);
				item_track->setText(CLMN_TITLE, track.titleWithTrackNumber());
				item_track->setToolTip(CLMN_TITLE, track.summaryString());
				item_track->setText(CLMN_YEAR, track.yearString());
				item_track->setNumb(CLMN_PLAY_COUNT, track.playCount());
			}
		}
	}
}

void Player::WidgetDataList::showByTracks(const Library& library)
{
	enum Columns {CLMN_TITLE, CLMN_YEAR, CLMN_PLAY_COUNT};
	initColumns({tr("Трек"), tr("Год"), tr("Прослушиваний")},
				{WIDTH_TITLE, WIDTH_YEAR, WIDTH_PLAY_COUNT});
	initSorting(CLMN_TITLE);

	for (const auto& [artist_title, artist] : library) {
		for (const auto& [album_title, album] : artist) {
			for (const auto& track : album) {
				auto item_track = new Base::WidgetTreeItem(this);
				item_track->setText(CLMN_TITLE, QStringLiteral("[%1 - %2] %3")
						.arg(artist_title, album_title, track.titleWithTrackNumber()));
				item_track->setToolTip(CLMN_TITLE, track.summaryString());
				item_track->setText(CLMN_YEAR, track.yearString());
				item_track->setNumb(CLMN_PLAY_COUNT, track.playCount());
			}
		}
	}
}

void Player::WidgetDataList::showByBestTracks(const Library& library)
{
	enum Columns {CLMN_TITLE, CLMN_YEAR, CLMN_TRACKS, CLMN_PLAY_COUNT};
	initColumns({tr("Группа / Трек"), tr("Год"), tr("Треков"), tr("Прослушиваний")},
				{WIDTH_TITLE, WIDTH_YEAR, WIDTH_TRACKS, WIDTH_PLAY_COUNT});
	initSorting(CLMN_TITLE);

	for (const auto& [artist_title, artist] : library) {
		auto item_artist = new Base::WidgetTreeItem(this, Global::Colors::tree_level_1);
		item_artist->setText(CLMN_TITLE, artist_title);
		item_artist->setToolTip(CLMN_TITLE, artist.summaryString());
		item_artist->setText(CLMN_YEAR, artist.yearString());
		item_artist->setNumb(CLMN_TRACKS, artist.tracksCount());
		item_artist->setNumb(CLMN_PLAY_COUNT, artist.playCount());

		for (const auto& [album_title, album] : artist) {
			for (const auto& track : album) {
				auto item_track = new Base::WidgetTreeItem(item_artist);
				if (artist_title == QStringLiteral("Разное")) {
					item_track->setText(CLMN_TITLE, track.title());
				} else {
					item_track->setText(CLMN_TITLE, QStringLiteral("[%1] %2")
							.arg(album_title, track.titleWithTrackNumber()));
				}
				item_track->setToolTip(CLMN_TITLE, track.summaryString());
				item_track->setText(CLMN_YEAR, track.yearString());
				item_track->setNumb(CLMN_PLAY_COUNT, track.playCount());
			}
		}
	}
}

void Player::WidgetDataList::showByGenres(const Library& library)
{
	enum Columns {CLMN_TITLE, CLMN_TRACKS};
	initColumns({tr("Жанр / Группа / Альбом / Трек"), tr("Треков")},
				{WIDTH_TITLE, WIDTH_TRACKS});
	initSorting(CLMN_TRACKS, Qt::DescendingOrder, true);

	auto genres = library.genres();

	for (const auto& [genre_title, genre_pair] : genres) {
		auto& artists_map = genre_pair.first;
		auto tracks_num = genre_pair.second;
		auto item_genre = new Base::WidgetTreeItem(this, Global::Colors::tree_level_3);
		item_genre->setText(CLMN_TITLE, genre_title);
		item_genre->setNumb(CLMN_TRACKS, tracks_num);

		for (const auto& [artist_title, albums_map] : artists_map) {
			auto item_artist = new Base::WidgetTreeItem(item_genre, Global::Colors::tree_level_2);
			if (genre_title.startsWith('*') && (artist_title != QStringLiteral("Разное"))) {
				// "* Rock"/"* Metal"
				item_artist->setText(CLMN_TITLE, QStringLiteral("%1 [%2]")
						.arg(artist_title, (*albums_map.begin()).second.front()->genre()));
			} else {
				item_artist->setText(CLMN_TITLE, artist_title);
			}

			for (const auto& [album_title, tracks] : albums_map) {
				auto item_album = new Base::WidgetTreeItem(item_artist, Global::Colors::tree_level_1);
				if (genre_title.startsWith('*') && (artist_title == QStringLiteral("Разное"))) {
					// "* Rock"/"* Metal"
					item_album->setText(CLMN_TITLE, QStringLiteral("%1 [%2]")
							.arg(album_title, tracks.front()->genre()));
				} else {
					item_album->setText(CLMN_TITLE, album_title);
				}

				for (auto track : tracks) {
					auto item_track = new Base::WidgetTreeItem(item_album);
					item_track->setText(CLMN_TITLE, track->titleWithTrackNumber());
					item_track->setToolTip(CLMN_TITLE, track->summaryString());
				}
			}
		}
	}
}

void Player::WidgetDataList::showByFormats(const Library& library)
{
	enum Columns {CLMN_TITLE, CLMN_YEAR, CLMN_ALBUMS, CLMN_TRACKS, CLMN_PLAY_COUNT};
	initColumns({tr("Формат / Группа / Альбом / Трек"), tr("Год"), tr("Альбомов"),
				 tr("Треков"), tr("Прослушиваний")},
				{WIDTH_TITLE, WIDTH_YEAR, WIDTH_ALBUMS, WIDTH_TRACKS, WIDTH_PLAY_COUNT});
	initSorting(CLMN_TITLE);

	auto formats = library.formats();

	for (const auto& [format_title, format_library] : formats) {
		auto item_format = new Base::WidgetTreeItem(this, Global::Colors::tree_level_3);
		item_format->setText(CLMN_TITLE, format_title);
		item_format->setToolTip(CLMN_TITLE, format_library.summaryString());
		item_format->setText(CLMN_YEAR, format_library.yearString());
		item_format->setNumb(CLMN_ALBUMS, format_library.albumsCount());
		item_format->setNumb(CLMN_TRACKS, format_library.tracksCount());
		item_format->setNumb(CLMN_PLAY_COUNT, format_library.playCount());

		for (const auto& [artist_title, artist] : format_library) {
			auto item_artist = new Base::WidgetTreeItem(item_format, Global::Colors::tree_level_2);
			item_artist->setText(CLMN_TITLE, artist_title);
			item_artist->setToolTip(CLMN_TITLE, artist.summaryString());
			item_artist->setText(CLMN_YEAR, artist.yearString());
			item_artist->setNumb(CLMN_ALBUMS, artist.albumsCount());
			item_artist->setNumb(CLMN_TRACKS, artist.tracksCount());
			item_artist->setNumb(CLMN_PLAY_COUNT, artist.playCount());

			for (const auto& [album_title, album] : artist) {
				auto item_album = new Base::WidgetTreeItem(item_artist, Global::Colors::tree_level_1);
				item_album->setText(CLMN_TITLE, album_title);
				item_album->setToolTip(CLMN_TITLE, album.summaryString());
				item_album->setText(CLMN_YEAR, album.yearString());
				item_album->setNumb(CLMN_TRACKS, album.tracksCount());
				item_album->setNumb(CLMN_PLAY_COUNT, album.playCount());

				for (const auto& track : album) {
					auto item_track = new Base::WidgetTreeItem(item_album);
					item_track->setText(CLMN_TITLE, track.titleWithTrackNumber());
					item_track->setToolTip(CLMN_TITLE, track.summaryString());
					item_track->setText(CLMN_YEAR, track.yearString());
					item_track->setNumb(CLMN_PLAY_COUNT, track.playCount());
				}
			}
		}
	}
}

void Player::WidgetDataList::showSummary(const Library& library)
{
	enum Columns {CLMN_TITLE, CLMN_YEAR, CLMN_PLAY_COUNT};
	initColumns({tr("Топ"), tr("Год"), tr("Прослушиваний")},
				{WIDTH_TITLE, WIDTH_YEAR, WIDTH_PLAY_COUNT});
	initSorting(-1, Qt::AscendingOrder, true);

	auto [played_artists, played_albums, played_tracks] = library.playedCount();
	auto top_artists = library.topArtists(TOP_SIZE);
	auto top_albums = library.topAlbums(TOP_SIZE);
	auto top_tracks = library.topTracks(TOP_SIZE);
	auto artists_count = library.artistsCount();
	auto albums_count = library.albumsCount();
	auto tracks_count = library.tracksCount();

	// artists
	auto item_top_artists = new Base::WidgetTreeItem(this, Global::Colors::tree_level_1);
	item_top_artists->setText(CLMN_TITLE, tr("Топ групп (прослушано %1/%2 - %3%)")
			.arg(played_artists).arg(artists_count).arg(100*played_artists/artists_count));

	for (int place = 0; auto [artist, play_count] : top_artists) {
		auto item_artist = new Base::WidgetTreeItem(item_top_artists);
		item_artist->setText(CLMN_TITLE, QStringLiteral("%1. %2")
				.arg(++place, 2, 10, QChar('0')).arg(artist->title()));
		item_artist->setToolTip(CLMN_TITLE, artist->summaryString());
		item_artist->setText(CLMN_YEAR, artist->yearString());
		item_artist->setNumb(CLMN_PLAY_COUNT, play_count);
	}

	// albums
	auto item_top_albums = new Base::WidgetTreeItem(this, Global::Colors::tree_level_1);
	item_top_albums->setText(CLMN_TITLE, tr("Топ альбомов (прослушано %1/%2 - %3%)")
			.arg(played_albums).arg(albums_count).arg(100*played_albums/albums_count));

	for (int place = 0; auto [album, play_count] : top_albums) {
		auto item_album = new Base::WidgetTreeItem(item_top_albums);
		item_album->setText(CLMN_TITLE, QStringLiteral("%1. [%2] %3")
				.arg(++place, 2, 10, QChar('0')).arg(album->artist(), album->title()));
		item_album->setToolTip(CLMN_TITLE, album->summaryString());
		item_album->setText(CLMN_YEAR, album->yearString());
		item_album->setNumb(CLMN_PLAY_COUNT, play_count);
	}

	// tracks
	auto item_top_tracks = new Base::WidgetTreeItem(this, Global::Colors::tree_level_1);
	item_top_tracks->setText(CLMN_TITLE, tr("Топ треков (прослушано %1/%2 - %3%)")
			.arg(played_tracks).arg(tracks_count).arg(100*played_tracks/tracks_count));

	for (int place = 0; auto [track, play_count] : top_tracks) {
		auto item_track = new Base::WidgetTreeItem(item_top_tracks);
		if (track->artist() == QStringLiteral("Разное")) {
			item_track->setText(CLMN_TITLE, QStringLiteral("%1. [%2] %3")
					.arg(++place, 2, 10, QChar('0')).arg(track->artist(), track->title()));
		} else {
			item_track->setText(CLMN_TITLE, QStringLiteral("%1. [%2 - %3] %4")
					.arg(++place, 2, 10, QChar('0')).arg(track->artist(), track->album(), track->title()));
		}
		item_track->setToolTip(CLMN_TITLE, track->summaryString());
		item_track->setText(CLMN_YEAR, track->yearString());
		item_track->setNumb(CLMN_PLAY_COUNT, play_count);
	}

	expandAll();
}

void Player::WidgetDataList::showHistoryArtists(const std::vector<Library>& libraries)
{
	enum Columns {CLMN_TITLE, CLMN_YEAR, CLMN_PLAY_COUNT};
	initColumns({tr("Топ"), tr("Год"), tr("Прослушиваний")},
				{WIDTH_TITLE, WIDTH_YEAR, WIDTH_PLAY_COUNT});
	initSorting(-1, Qt::AscendingOrder, true);

	for (unsigned int i = 1; i < libraries.size(); ++i) {
		const auto& prev_library = libraries[i-1];
		const auto& library = libraries[i];

		auto [played_artists, played_albums, played_tracks] = library.playedCount();
		auto top_artists = library.topArtists(TOP_SIZE);
		auto artists_count = library.artistsCount();

		auto item_library = new Base::WidgetTreeItem(this, Global::Colors::tree_level_1);
		item_library->setText(CLMN_TITLE, tr("%1 → %2: Топ групп (прослушано %3/%4 - %5%)")
				.arg(prev_library.titleOnlyDate(), library.titleOnlyDate())
				.arg(played_artists).arg(artists_count).arg(100*played_artists/artists_count));
		item_library->setNumb(CLMN_PLAY_COUNT, library.playCount());

		for (int place = 0; auto [artist, play_count] : top_artists) {
			auto item_artist = new Base::WidgetTreeItem(item_library);
			item_artist->setText(CLMN_TITLE, QStringLiteral("%1. %2")
					.arg(++place, 2, 10, QChar('0')).arg(artist->title()));
			item_artist->setToolTip(CLMN_TITLE, artist->summaryString());
			item_artist->setText(CLMN_YEAR, artist->yearString());
			item_artist->setNumb(CLMN_PLAY_COUNT, play_count);
		}
	}

	expandAll();
}

void Player::WidgetDataList::showHistoryAlbums(const std::vector<Library>& libraries)
{
	enum Columns {CLMN_TITLE, CLMN_YEAR, CLMN_PLAY_COUNT};
	initColumns({tr("Топ"), tr("Год"), tr("Прослушиваний")},
				{WIDTH_TITLE, WIDTH_YEAR, WIDTH_PLAY_COUNT});
	initSorting(-1, Qt::AscendingOrder, true);

	for (unsigned int i = 1; i < libraries.size(); ++i) {
		const auto& prev_library = libraries[i-1];
		const auto& library = libraries[i];

		auto [played_artists, played_albums, played_tracks] = library.playedCount();
		auto top_albums = library.topAlbums(TOP_SIZE);
		auto albums_count = library.albumsCount();

		auto item_library = new Base::WidgetTreeItem(this, Global::Colors::tree_level_1);
		item_library->setText(CLMN_TITLE, tr("%1 → %2: Топ альбомов (прослушано %3/%4 - %5%)")
				.arg(prev_library.titleOnlyDate(), library.titleOnlyDate())
				.arg(played_albums).arg(albums_count).arg(100*played_albums/albums_count));
		item_library->setNumb(CLMN_PLAY_COUNT, library.playCount());

		for (int place = 0; auto [album, play_count] : top_albums) {
			auto item_album = new Base::WidgetTreeItem(item_library);
			item_album->setText(CLMN_TITLE, QStringLiteral("%1. [%2] %3")
					.arg(++place, 2, 10, QChar('0')).arg(album->artist(), album->title()));
			item_album->setToolTip(CLMN_TITLE, album->summaryString());
			item_album->setText(CLMN_YEAR, album->yearString());
			item_album->setNumb(CLMN_PLAY_COUNT, play_count);
		}
	}

	expandAll();
}

void Player::WidgetDataList::showHistoryTracks(const std::vector<Library>& libraries)
{
	enum Columns {CLMN_TITLE, CLMN_YEAR, CLMN_PLAY_COUNT};
	initColumns({tr("Топ"), tr("Год"), tr("Прослушиваний")},
				{WIDTH_TITLE, WIDTH_YEAR, WIDTH_PLAY_COUNT});
	initSorting(-1, Qt::AscendingOrder, true);

	for (unsigned int i = 1; i < libraries.size(); ++i) {
		const auto& prev_library = libraries[i-1];
		const auto& library = libraries[i];

		auto [played_artists, played_albums, played_tracks] = library.playedCount();
		auto top_tracks = library.topTracks(TOP_SIZE);
		auto tracks_count = library.tracksCount();

		auto item_library = new Base::WidgetTreeItem(this, Global::Colors::tree_level_1);
		item_library->setText(CLMN_TITLE, tr("%1 → %2: Топ треков (прослушано %3/%4 - %5%)")
				.arg(prev_library.titleOnlyDate(), library.titleOnlyDate())
				.arg(played_tracks).arg(tracks_count).arg(100*played_tracks/tracks_count));
		item_library->setNumb(CLMN_PLAY_COUNT, library.playCount());

		for (int place = 0; auto [track, play_count] : top_tracks) {
			auto item_track = new Base::WidgetTreeItem(item_library);
			if (track->artist() == QStringLiteral("Разное")) {
				item_track->setText(CLMN_TITLE, QStringLiteral("%1. [%2] %3")
						.arg(++place, 2, 10, QChar('0')).arg(track->artist(), track->title()));
			} else {
				item_track->setText(CLMN_TITLE, QStringLiteral("%1. [%2 - %3] %4")
						.arg(++place, 2, 10, QChar('0')).arg(track->artist(), track->album(), track->title()));
			}
			item_track->setToolTip(CLMN_TITLE, track->summaryString());
			item_track->setText(CLMN_YEAR, track->yearString());
			item_track->setNumb(CLMN_PLAY_COUNT, play_count);
		}
	}

	expandAll();
}
