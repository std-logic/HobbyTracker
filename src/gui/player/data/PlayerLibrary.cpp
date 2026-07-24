#include "PlayerLibrary.h"

#include <unordered_set>

std::vector<Player::Library::TopArtistsData> Player::Library::topArtists(int top_size) const
{
	std::vector<TopArtistsData> artists_list;
	for (const auto& [artist_title, artist] : _artists) {
		artists_list.emplace_back(TopArtistsData{&artist, artist.playCount()});
	}
	std::sort(artists_list.begin(), artists_list.end(),
			  [](const TopArtistsData& a, const TopArtistsData& b)
			  {return (a.second > b.second);});
	return std::vector<TopArtistsData>{artists_list.begin(), artists_list.begin()+top_size};
}

std::vector<Player::Library::TopAlbumsData> Player::Library::topAlbums(int top_size) const
{
	std::vector<TopAlbumsData> albums_list;
	for (const auto& [artist_title, artist] : _artists) {
		for (const auto& [album_title, album] : artist) {
			albums_list.emplace_back(TopAlbumsData{&album, album.playCount()});
		}
	}
	std::sort(albums_list.begin(), albums_list.end(),
			  [](const TopAlbumsData& a, const TopAlbumsData& b)
			  {return (a.second > b.second);});
	return std::vector<TopAlbumsData>{albums_list.begin(), albums_list.begin()+top_size};
}

std::vector<Player::Library::TopTracksData> Player::Library::topTracks(int top_size) const
{
	std::vector<TopTracksData> tracks_list;
	for (const auto& [artist_title, artist] : _artists) {
		for (const auto& [album_title, album] : artist) {
			for (const auto& track : album) {
				tracks_list.emplace_back(TopTracksData{&track, track.playCount()});
			}
		}
	}
	std::sort(tracks_list.begin(), tracks_list.end(),
			  [](const TopTracksData& a, const TopTracksData& b)
			  {return (a.second > b.second);});
	return std::vector<TopTracksData>{tracks_list.begin(), tracks_list.begin()+top_size};
}

std::tuple<int, int, int> Player::Library::playedCount() const
{
	int played_artists = 0, played_albums = 0, played_tracks = 0;
	for (const auto& [artist_title, artist] : _artists) {
		bool played_artist_found = false;
		for (const auto& [album_title, album] : artist) {
			bool played_album_found = false;
			for (const auto& track : album) {
				if (track.playCount()) {
					if (!played_artist_found) {
						played_artist_found = true;
						++played_artists;
					}
					if (!played_album_found) {
						played_album_found = true;
						++played_albums;
					}
					++played_tracks;
				}
			}
		}
	}
	return std::make_tuple(played_artists, played_albums, played_tracks);
}

Player::Library::GenresData Player::Library::genres() const
{
	GenresData genres;
	for (const auto& [artist_title, artist] : _artists) {
		for (const auto& [album_title, album] : artist) {
			for (const auto& track : album) {
				auto& item_genre = genres[track.genre()];
				if (item_genre.isTitleEmpty()) { item_genre.setTitle(_title); }
				auto& item_artist = item_genre[track.artist()];
				if (item_artist.isTitleEmpty()) { item_artist.setTitle(track.artist()); }
				auto& item_album = item_artist[track.album()];
				if (item_album.isTitleEmpty()) { item_album.setTitle(track.album()); }
				item_album.addTrack(track);
			}
		}
	}
	return genres;
}

Player::Library::FormatsData Player::Library::formats() const
{
	FormatsData formats;
	for (const auto& [artist_title, artist] : _artists) {
		for (const auto& [album_title, album] : artist) {
			for (const auto& track : album) {
				auto& item_format = formats[track.format()];
				if (item_format.isTitleEmpty()) { item_format.setTitle(_title); }
				auto& item_artist = item_format[track.artist()];
				if (item_artist.isTitleEmpty()) { item_artist.setTitle(track.artist()); }
				auto& item_album = item_artist[track.album()];
				if (item_album.isTitleEmpty()) { item_album.setTitle(track.album()); }
				item_album.addTrack(track);
			}
		}
	}
	return formats;
}

Player::Library::Summary Player::Library::summary() const
{
	Summary sum;
	std::unordered_set<QString> list_of_genres;
	for (const auto& [artist_title, artist] : _artists) {
		for (const auto& [album_title, album] : artist) {
			for (const auto& track : album) {
				list_of_genres.insert(track.genre());
				Helper::checkMinMax(track.year(), &sum.min_year, &sum.max_year);
			}
		}
	}
	sum.title = titleOnlyDate();
	sum.artists_num = artistsCount();
	sum.albums_num = albumsCount();
	sum.tracks_num = tracksCount();
	sum.play_count = playCount();
	sum.genres_num = list_of_genres.size();
	return sum;
}

QString Player::Library::summaryString() const
{
	QString text;
	text += QString("Файл: %1").arg(_title);
	text += QString("\nГод: %1").arg(yearString());
	text += QString("\nГрупп: %1").arg(artistsCount());
	text += QString("\nАльбомов: %1").arg(albumsCount());
	text += QString("\nТреков: %1").arg(tracksCount());
	text += QString("\nПрослушиваний: %1").arg(playCount());
	text += QString("\nДлина: %1").arg(Helper::timeString(time()));
	text += QString("\nРазмер: %1").arg(Helper::sizeString(size()));
	return text;
}
