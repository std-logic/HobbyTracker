#include "PlayerWidgetChart.h"
#include "../common/PlayerCommon.h"
#include "../data/PlayerLibrary.h"

Player::WidgetChart::WidgetChart(QWidget* parent)
	: Base::WidgetChart{parent}
{
}

void Player::WidgetChart::update(const Library& library)
{
	clearChart();
	if (library.empty()) { return; }
	switch (static_cast<ChartViewModes>(_view_mode)) {
		case ChartViewModes::ByPlayCounts:	showByPlayCounts(library);	break;
		case ChartViewModes::ByDecades:		showByDecades(library);		break;
		default: return;
	}
}

void Player::WidgetChart::update(const std::vector<Library>& libraries)
{
	clearChart();
	if (libraries.empty()) { return; }
	switch (static_cast<ChartViewModes>(_view_mode)) {
		case ChartViewModes::HistoryPlayCounts:	showHistoryPlayCounts(libraries);	break;
		case ChartViewModes::HistoryArtists:	showHistoryArtists(libraries);		break;
		case ChartViewModes::HistoryAlbums:		showHistoryAlbums(libraries);		break;
		case ChartViewModes::HistoryTracks:		showHistoryTracks(libraries);		break;
		default: return;
	}
}

void Player::WidgetChart::showByPlayCounts(const Library& library)
{
	chart()->setTitle(tr("Распределение по прослушиваниям"));
	const uint32_t step = 10;
	std::map<uint32_t, std::pair<QString, uint32_t>> list;
	uint32_t min_x = std::numeric_limits<uint32_t>::max(), max_x = std::numeric_limits<uint32_t>::min();
	for (const auto& [artist_title, artist] : library) {
		for (const auto& [album_title, album] : artist) {
			for (const auto& track : album) {
				uint32_t val_x = (track.playCount() / step) * step;
				Helper::checkMinMaxAny(val_x, &min_x, &max_x);
				++list[val_x].second;
			}
		}
	}
	for (uint32_t val_x = min_x; val_x <= max_x; val_x += step) {
		list[val_x].first = QStringLiteral("%1-%2").arg(val_x).arg(val_x + step - 1);
	}
	updateBars(list);
}

void Player::WidgetChart::showByDecades(const Library& library)
{
	chart()->setTitle(tr("Распределение по десятилетиям"));
	const uint32_t step = 10;
	std::map<uint32_t, std::pair<QString, uint32_t>> list;
	uint32_t min_x = Global::undefined_value, max_x = Global::undefined_value;
	for (const auto& [artist_title, artist] : library) {
		for (const auto& [album_title, album] : artist) {
			for (const auto& track : album) {
				auto val_x = (track.year() / step) * step;
				Helper::checkMinMax(val_x, &min_x, &max_x);
				++list[val_x].second;
			}
		}
	}
	if (list.contains(Global::undefined_value)) {
		list[Global::undefined_value].first = Helper::epochString(Global::undefined_value, step);
	}
	for (uint32_t val_x = min_x; val_x <= max_x; val_x += step) {
		list[val_x].first = Helper::epochString(val_x, step);
	}
	updateBars(list);
}

void Player::WidgetChart::showHistoryPlayCounts(const std::vector<Library>& libraries)
{
	chart()->setTitle(tr("Прирост прослушиваний"));
	std::map<QString, uint32_t> list;
	for (size_t i = 1; i < libraries.size(); ++i) {
		list[libraries[i].titleOnlyDate()] = libraries[i].playCount();
	}
	updateBars(list);
}

void Player::WidgetChart::showHistoryArtists(const std::vector<Library>& libraries)
{
	chart()->setTitle(tr("Прирост групп"));
	std::map<QString, uint32_t> list;
	for (size_t i = 1; i < libraries.size(); ++i) {
		list[libraries[i].titleOnlyDate()] =
				libraries[i].artistsCount() - libraries[i-1].artistsCount();
	}
	updateBars(list);
}

void Player::WidgetChart::showHistoryAlbums(const std::vector<Library>& libraries)
{
	chart()->setTitle(tr("Прирост альбомов"));
	std::map<QString, uint32_t> list;
	for (size_t i = 1; i < libraries.size(); ++i) {
		list[libraries[i].titleOnlyDate()] =
				libraries[i].albumsCount() - libraries[i-1].albumsCount();
	}
	updateBars(list);
}

void Player::WidgetChart::showHistoryTracks(const std::vector<Library>& libraries)
{
	chart()->setTitle(tr("Прирост треков"));
	std::map<QString, uint32_t> list;
	for (size_t i = 1; i < libraries.size(); ++i) {
		list[libraries[i].titleOnlyDate()] =
				libraries[i].tracksCount() - libraries[i-1].tracksCount();
	}
	updateBars(list);
}
