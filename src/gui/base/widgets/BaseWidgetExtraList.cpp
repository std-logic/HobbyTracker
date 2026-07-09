#include "BaseWidgetExtraList.h"
#include "BaseWidgetTreeItem.h"
#include "../data/BaseExtraList.h"

Base::WidgetExtraList::WidgetExtraList(QWidget* parent)
	: Base::WidgetTree{parent}
{
}

void Base::WidgetExtraList::update(const ExtraList& data_list)
{
	clear();
	showByGroups(data_list);
}

void Base::WidgetExtraList::showByGroups(const ExtraList& data_list)
{
	enum Columns {CLMN_TITLE, CLMN_COUNT, CLMN_NOTES};
	initColumns({tr("Список / Запись"), tr("К-во"), tr("Комментарий")},
				{WIDTH_TITLE, WIDTH_COUNT, WIDTH_NOTES});
	initSorting(CLMN_TITLE);

	auto extra_by_groups = data_list.extraByGroups();

	for (const auto& [group, extras] : extra_by_groups) {
		auto item_group = new Base::WidgetTreeItem(this, Global::Colors::tree_level_1);
		item_group->setText(CLMN_TITLE, group);
		item_group->setNumb(CLMN_COUNT, extras.size());

		for (const auto extra : extras) {
			auto item_extra = new Base::WidgetTreeItem(item_group);
			item_extra->setText(CLMN_TITLE, extra->title());
			item_extra->setText(CLMN_NOTES, extra->notes());
			item_extra->setId(extra->id());
		}
	}
}
