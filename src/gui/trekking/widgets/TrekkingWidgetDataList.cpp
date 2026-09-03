#include "TrekkingWidgetDataList.h"
#include "../common/TrekkingCommon.h"
#include "../data/TrekkingDataList.h"

#include <gui/base/widgets/BaseWidgetTreeItem.h>

Trekking::WidgetDataList::WidgetDataList(QWidget* parent)
	: Base::WidgetTree{parent}
{
}

void Trekking::WidgetDataList::update(const DataList& data_list)
{
	clear();
	setRootIsDecorated(static_cast<DataListViewModes>(_view_mode) != DataListViewModes::Simple);
	switch (static_cast<DataListViewModes>(_view_mode)) {
		case DataListViewModes::Simple:			showSimple(data_list);			break;
		case DataListViewModes::ByCountries:	showByCountries(data_list);		break;
		case DataListViewModes::ByRegions:		showByRegions(data_list);		break;
		case DataListViewModes::ByKinds:		showByKinds(data_list);			break;
		default: return;
	}
}

void Trekking::WidgetDataList::showSimple(const DataList& data_list)
{
	enum Columns {CLMN_DATE, CLMN_TIME, CLMN_DIST, CLMN_PEAK,
				  CLMN_KIND, CLMN_COUNTRIES, CLMN_PLACES};
	initColumns({tr("Даты"), tr("Ночёвок"), tr("Километров"), tr("Высшая точка"),
				 tr("Тип"), tr("Страны"), tr("Место")},
				{WIDTH_DATE, WIDTH_TIME, WIDTH_DIST, WIDTH_PEAK,
				 WIDTH_KIND, WIDTH_COUNTRIES, WIDTH_PLACES});
	initSorting(CLMN_DATE, Qt::DescendingOrder);

	for (const auto& track : data_list) {
		auto item_track = new Base::WidgetTreeItem(this);
		item_track->setText(CLMN_DATE, track.dates());
		item_track->setNumb(CLMN_TIME, track.time());
		item_track->setNumb(CLMN_DIST, track.dist());
		item_track->setNumb(CLMN_PEAK, track.peak());
		item_track->setText(CLMN_KIND, track.kind());
		item_track->setText(CLMN_COUNTRIES, track.countriesToString(QStringLiteral(" • ")));
		item_track->setText(CLMN_PLACES, track.places());
		item_track->setId(track.id());
	}
}

void Trekking::WidgetDataList::showByCountries(const DataList& data_list)
{
	enum Columns {CLMN_DATE, CLMN_COUNT, CLMN_TIME, CLMN_DIST,
				  CLMN_PEAK, CLMN_KIND, CLMN_COUNTRIES, CLMN_PLACES};
	initColumns({tr("Страна / Даты"), tr("К-во"), tr("Ночёвок"), tr("Километров"),
				 tr("Высшая точка"), tr("Тип"), tr("Страны"), tr("Место")},
				{WIDTH_DATE, WIDTH_COUNT, WIDTH_TIME, WIDTH_DIST,
				 WIDTH_PEAK, WIDTH_KIND, WIDTH_COUNTRIES, WIDTH_PLACES});
	initSorting(CLMN_DATE);

	auto tracks_by_countries = data_list.tracksByCountries();

	for (const auto& [country, tracks] : tracks_by_countries) {
		auto item_country = new Base::WidgetTreeItem(this, Global::Colors::tree_level_1);
		item_country->setCountry(CLMN_DATE, country);
		item_country->setNumb(CLMN_COUNT, tracks.size());
		uint32_t country_time = 0, country_dist = 0, country_peak = Global::undefined_value;

		for (const auto track : tracks) {
			auto item_track = new Base::WidgetTreeItem(item_country);
			item_track->setText(CLMN_DATE, track->dates());
			item_track->setNumb(CLMN_TIME, track->time());
			item_track->setNumb(CLMN_DIST, track->dist());
			item_track->setNumb(CLMN_PEAK, track->peak());
			item_track->setText(CLMN_KIND, track->kind());
			item_track->setText(CLMN_COUNTRIES, track->countriesToString(QStringLiteral(" • ")));
			item_track->setText(CLMN_PLACES, track->places());
			item_track->setId(track->id());
			country_time += track->time();
			country_dist += track->dist();
			Helper::checkMax(track->peak(), &country_peak);
		}

		item_country->setNumb(CLMN_TIME, country_time);
		item_country->setNumb(CLMN_DIST, country_dist);
		item_country->setNumb(CLMN_PEAK, country_peak);
	}
}

void Trekking::WidgetDataList::showByRegions(const DataList& data_list)
{
	enum Columns {CLMN_DATE, CLMN_COUNT, CLMN_TIME, CLMN_DIST,
				  CLMN_PEAK, CLMN_KIND, CLMN_COUNTRIES, CLMN_PLACES};
	initColumns({tr("Регион / Страна / Даты"), tr("К-во"), tr("Ночёвок"), tr("Километров"),
				 tr("Высшая точка"), tr("Тип"), tr("Страны"), tr("Место")},
				{WIDTH_DATE, WIDTH_COUNT, WIDTH_TIME, WIDTH_DIST,
				 WIDTH_PEAK, WIDTH_KIND, WIDTH_COUNTRIES, WIDTH_PLACES});
	initSorting(CLMN_DATE);

	auto tracks_by_regions = data_list.tracksByRegions();

	for (const auto& [region, tracks_by_countries] : tracks_by_regions) {
		auto item_region = new Base::WidgetTreeItem(this, Global::Colors::tree_level_2);
		item_region->setText(CLMN_DATE, region);
		std::unordered_set<QString> ids;
		uint32_t region_time = 0, region_dist = 0, region_peak = Global::undefined_value;

		for (const auto& [country, tracks] : tracks_by_countries) {
			auto item_country = new Base::WidgetTreeItem(item_region, Global::Colors::tree_level_1);
			item_country->setCountry(CLMN_DATE, country);
			item_country->setNumb(CLMN_COUNT, tracks.size());
			uint32_t country_time = 0, country_dist = 0, country_peak = Global::undefined_value;

			for (const auto track : tracks) {
				auto item_track = new Base::WidgetTreeItem(item_country);
				item_track->setText(CLMN_DATE, track->dates());
				item_track->setNumb(CLMN_TIME, track->time());
				item_track->setNumb(CLMN_DIST, track->dist());
				item_track->setNumb(CLMN_PEAK, track->peak());
				item_track->setText(CLMN_KIND, track->kind());
				item_track->setText(CLMN_COUNTRIES, track->countriesToString(QStringLiteral(" • ")));
				item_track->setText(CLMN_PLACES, track->places());
				item_track->setId(track->id());
				if (!ids.contains(track->id())) {
					region_time += track->time();
					region_dist += track->dist();
					Helper::checkMax(track->peak(), &region_peak);
				}
				ids.insert(track->id());
				country_time += track->time();
				country_dist += track->dist();
				Helper::checkMax(track->peak(), &country_peak);
			}

			item_country->setNumb(CLMN_TIME, country_time);
			item_country->setNumb(CLMN_DIST, country_dist);
			item_country->setNumb(CLMN_PEAK, country_peak);
		}

		item_region->setNumb(CLMN_COUNT, ids.size());
		item_region->setNumb(CLMN_TIME, region_time);
		item_region->setNumb(CLMN_DIST, region_dist);
		item_region->setNumb(CLMN_PEAK, region_peak);
	}
}

void Trekking::WidgetDataList::showByKinds(const DataList& data_list)
{
	enum Columns {CLMN_DATE, CLMN_COUNT, CLMN_TIME, CLMN_DIST,
				  CLMN_PEAK, CLMN_COUNTRIES, CLMN_PLACES};
	initColumns({tr("Тип / Даты"), tr("К-во"), tr("Ночёвок"), tr("Километров"),
				 tr("Высшая точка"), tr("Страны"), tr("Место")},
				{WIDTH_DATE, WIDTH_COUNT, WIDTH_TIME, WIDTH_DIST,
				 WIDTH_PEAK, WIDTH_COUNTRIES, WIDTH_PLACES});
	initSorting(CLMN_DATE);

	auto tracks_by_kinds = data_list.tracksByKinds();

	for (const auto& [kind, tracks] : tracks_by_kinds) {
		auto item_kind = new Base::WidgetTreeItem(this, Global::Colors::tree_level_1);
		item_kind->setText(CLMN_DATE, kind);
		item_kind->setNumb(CLMN_COUNT, tracks.size());
		uint32_t kind_time = 0, kind_dist = 0, kind_peak = Global::undefined_value;

		for (const auto track : tracks) {
			auto item_track = new Base::WidgetTreeItem(item_kind);
			item_track->setText(CLMN_DATE, track->dates());
			item_track->setNumb(CLMN_TIME, track->time());
			item_track->setNumb(CLMN_DIST, track->dist());
			item_track->setNumb(CLMN_PEAK, track->peak());
			item_track->setText(CLMN_COUNTRIES, track->countriesToString(QStringLiteral(" • ")));
			item_track->setText(CLMN_PLACES, track->places());
			item_track->setId(track->id());
			kind_time += track->time();
			kind_dist += track->dist();
			Helper::checkMax(track->peak(), &kind_peak);
		}

		item_kind->setNumb(CLMN_TIME, kind_time);
		item_kind->setNumb(CLMN_DIST, kind_dist);
		item_kind->setNumb(CLMN_PEAK, kind_peak);
	}
}
