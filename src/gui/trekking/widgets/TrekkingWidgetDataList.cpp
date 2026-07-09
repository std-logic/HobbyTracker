#include "TrekkingWidgetDataList.h"
#include "../common/TrekkingCommon.h"
#include "../data/TrekkingDataList.h"

#include <gui/base/widgets/BaseWidgetTreeItem.h>

Trekking::WidgetDataList::WidgetDataList(QWidget* parent)
	: Base::WidgetTree{parent}
{
	setRootIsDecorated(false);
}

void Trekking::WidgetDataList::update(const DataList& data_list)
{
	clear();
	setRootIsDecorated(static_cast<DataListViewModes>(_view_mode) != DataListViewModes::Simple);
	switch (static_cast<DataListViewModes>(_view_mode)) {
		case DataListViewModes::Simple:			showSimple(data_list);			break;
		case DataListViewModes::ByCountries:	showByCountries(data_list);		break;
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
	initSorting(CLMN_DATE);

	for (const auto& data : data_list) {
		auto item_data = new Base::WidgetTreeItem(this);
		item_data->setText(CLMN_DATE, data.dates());
		item_data->setNumb(CLMN_TIME, data.time());
		item_data->setNumb(CLMN_DIST, data.dist());
		item_data->setNumb(CLMN_PEAK, data.peak());
		item_data->setText(CLMN_KIND, data.kind());
		item_data->setText(CLMN_COUNTRIES, data.countriesToString(QStringLiteral(" • ")));
		item_data->setText(CLMN_PLACES, data.places());
		item_data->setId(data.id());
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
		item_country->setText(CLMN_DATE, country);
		item_country->setNumb(CLMN_COUNT, tracks.size());

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
		}
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

		for (const auto track : tracks) {
			auto item_track = new Base::WidgetTreeItem(item_kind);
			item_track->setText(CLMN_DATE, track->dates());
			item_track->setNumb(CLMN_TIME, track->time());
			item_track->setNumb(CLMN_DIST, track->dist());
			item_track->setNumb(CLMN_PEAK, track->peak());
			item_track->setText(CLMN_COUNTRIES, track->countriesToString(QStringLiteral(" • ")));
			item_track->setText(CLMN_PLACES, track->places());
			item_track->setId(track->id());
		}
	}
}
