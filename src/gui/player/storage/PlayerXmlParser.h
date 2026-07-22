#pragma once

#include "../data/PlayerTrack.h"

#include <QString>

#include <list>

namespace Player
{

class XmlParser
{
public:
	XmlParser() = delete;

	static std::list<Track> readFile(const QString& file_name);
};

} // namespace Player
