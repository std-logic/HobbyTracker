#include "BaseWidgetTreeItem.h"

#include <common/Global.h>
#include <common/Helper.h>

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
	setBackground(column, Helper::ratingColor(rating));
}

void Base::WidgetTreeItem::setBold(int column, bool enable)
{
	auto default_font = font(column);
	default_font.setBold(enable);
	setFont(column, default_font);
}

void Base::WidgetTreeItem::setBoldEverywhere(bool enable)
{
	for (auto column = 0; column < treeWidget()->columnCount(); ++column) {
		setBold(column, enable);
	}
}

void Base::WidgetTreeItem::setBackgroundEverywhere(const QBrush& brush)
{
	for (auto column = 0; column < treeWidget()->columnCount(); ++column) {
		setBackground(column, brush);
	}
}
