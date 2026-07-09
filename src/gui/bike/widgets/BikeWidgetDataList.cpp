#include "BikeWidgetDataList.h"
#include "../data/BikeDataList.h"

#include <gui/base/widgets/BaseWidgetTreeItem.h>

Bike::WidgetDataList::WidgetDataList(QWidget* parent)
	: Base::WidgetTree{parent}
{
	setRootIsDecorated(false);
}

void Bike::WidgetDataList::update(const DataList& data_list)
{
	clear();
	showSimple(data_list);
}

void Bike::WidgetDataList::showSimple(const DataList& data_list)
{
	enum Columns {CLMN_YEAR, CLMN_TIME, CLMN_DIST};
	initColumns({tr("Год"), tr("Часов"), tr("Километров")},
				{WIDTH_YEAR, WIDTH_TIME, WIDTH_DIST});
	initSorting(CLMN_YEAR);

	for (const auto& data : data_list) {
		auto item_data = new Base::WidgetTreeItem(this);
		item_data->setNumb(CLMN_YEAR, data.year());
		item_data->setNumb(CLMN_TIME, data.time());
		item_data->setNumb(CLMN_DIST, data.dist());
		item_data->setId(data.id());
	}
}
