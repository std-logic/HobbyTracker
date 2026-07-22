#pragma once

#include "../data/PlayerLibrary.h"

#include <QStringList>

#include <list>
#include <unordered_map>

namespace Player
{

class Storage
{
public:
	Storage() = default;

public:
	Library readLibrary(const QStringList& file_names);
	std::vector<Library> readLibraries(const QStringList& file_names);

private:
	std::list<Track> readTracks(const QString& file_name);
	std::list<Track> calcTracksDiff(std::list<Track> tracks_1, std::list<Track> tracks_2);
	QString createLibraryTitleFromFileName(const QString& file_name);
	QString createLibraryTitleFromFileNames(const QString& file_name_1, const QString& file_name_2);
	Library createLibraryFromTracks(const QString& title, const std::list<Track>& tracks);

private:
	std::unordered_map<QString, std::list<Track>> _tracks_cache;
};

} // namespace Player
