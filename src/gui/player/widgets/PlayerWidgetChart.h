#pragma once

#include <gui/base/widgets/BaseWidgetChart.h>

namespace Player
{

class Library;

class WidgetChart : public Base::WidgetChart
{
	Q_OBJECT
public:
	explicit WidgetChart(QWidget* parent = nullptr);
	~WidgetChart() = default;

	void update(const Library& library);
	void update(const std::vector<Library>& libraries);

signals:

private:
	void showByPlayCounts(const Library& library);
	void showByDecades(const Library& library);
	void showHistoryPlayCounts(const std::vector<Library>& libraries);
	void showHistoryArtists(const std::vector<Library>& libraries);
	void showHistoryAlbums(const std::vector<Library>& libraries);
	void showHistoryTracks(const std::vector<Library>& libraries);
};

} // namespace Player
