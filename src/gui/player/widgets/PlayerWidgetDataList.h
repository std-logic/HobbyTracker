#pragma once

#include <gui/base/widgets/BaseWidgetTree.h>

namespace Player
{

class Library;

class WidgetDataList : public Base::WidgetTree
{
	Q_OBJECT
public:
	explicit WidgetDataList(QWidget* parent = nullptr);
	~WidgetDataList() = default;

	void update(const Library& library);
	void update(const std::vector<Library>& libraries);

signals:

private:
	void showByArtists(const Library& library);
	void showByAlbums(const Library& library);
	void showByTracks(const Library& library);
	void showByBestTracks(const Library& library);
	void showByGenres(const Library& library);
	void showSummary(const Library& library);
	void showHistory(const std::vector<Library>& libraries);

private:
	static const int TOP_SIZE_FOR_SUMMARY = 10;
	static const int TOP_SIZE_FOR_HISTORY = 3;

	static const int WIDTH_TITLE = 0; // stretched
	static const int WIDTH_YEAR = 120;
	static const int WIDTH_ALBUMS = 100;
	static const int WIDTH_TRACKS = 100;
	static const int WIDTH_PLAY_COUNT = 130;
};

} // namespace Player
