#include "BikeWidgetDataList.h"
#include "../data/BikeDataList.h"

#include <gui/base/widgets/BaseWidgetTreeItem.h>

Bike::WidgetDataList::WidgetDataList(QWidget* parent)
	: Base::WidgetTree{parent}
{
	setRootIsDecorated(false);
}

void Bike::WidgetDataList::update(const DataList& list)
{
	clear();
	showSimple(list);
}

void Bike::WidgetDataList::showSimple(const DataList& list)
{
	enum Columns {CLMN_YEAR, CLMN_DIST, CLMN_TIME};
	initColumns({tr("Год"), tr("Пробег, км"), tr("Время, ч")},
				{WIDTH_YEAR, WIDTH_DIST, WIDTH_TIME});
	initSorting(CLMN_YEAR);

	for (const auto& data : list) {
		auto item_data = new Base::WidgetTreeItem(this);
		item_data->setNumb(CLMN_YEAR, data.year());
		item_data->setNumb(CLMN_DIST, data.dist());
		item_data->setNumb(CLMN_TIME, data.time());
		item_data->setId(data.id());
	}
}
