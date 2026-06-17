#include "BaseWidgetTreeItem.h"

#include <common/Global.h>

#include <QTreeWidget>

Base::WidgetTreeItem::WidgetTreeItem(int type)
	: QTreeWidgetItem{type}
{
}

Base::WidgetTreeItem::WidgetTreeItem(QTreeWidget* parent, int type)
	: QTreeWidgetItem{parent, type}
{
}

Base::WidgetTreeItem::WidgetTreeItem(QTreeWidgetItem* parent, int type)
	: QTreeWidgetItem{parent, type}
{
}

Base::WidgetTreeItem::WidgetTreeItem(const QBrush& brush, int type)
	: QTreeWidgetItem{type}
{
	setBackgroundEverywhere(brush);
}

Base::WidgetTreeItem::WidgetTreeItem(QTreeWidget* parent, const QBrush& brush, int type)
	: QTreeWidgetItem{parent, type}
{
	setBackgroundEverywhere(brush);
}

Base::WidgetTreeItem::WidgetTreeItem(QTreeWidgetItem* parent, const QBrush& brush, int type)
	: QTreeWidgetItem{parent, type}
{
	setBackgroundEverywhere(brush);
}

void Base::WidgetTreeItem::setRating(int column, const QVariant& value)
{
	setNumb(column, value);
	auto rating = value.toUInt();
	if ((1 <= rating) && (rating <= 10)) {
		setBackground(column, Global::Colors::rating[rating-1]);
	}
}

void Base::WidgetTreeItem::setBold(bool enable)
{
	for (auto i = 0; i < columnCount(); ++i) {
		auto default_font = font(i);
		default_font.setBold(enable);
		setFont(i, default_font);
	}
}

void Base::WidgetTreeItem::setBackgroundEverywhere(const QBrush& brush)
{
	for (auto i = 0; i < treeWidget()->columnCount(); ++i) {
		setBackground(i, brush);
	}
}
