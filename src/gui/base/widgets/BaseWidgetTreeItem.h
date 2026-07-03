#pragma once

#include <QTreeWidgetItem>

namespace Base
{

class WidgetTreeItem : public QTreeWidgetItem
{
public:
	explicit WidgetTreeItem(int type = QTreeWidgetItem::Type);
	explicit WidgetTreeItem(QTreeWidget* parent, int type = QTreeWidgetItem::Type);
	explicit WidgetTreeItem(QTreeWidgetItem* parent, int type = QTreeWidgetItem::Type);
	explicit WidgetTreeItem(const QBrush& brush, int type = QTreeWidgetItem::Type);
	explicit WidgetTreeItem(QTreeWidget* parent, const QBrush& brush, int type = QTreeWidgetItem::Type);
	explicit WidgetTreeItem(QTreeWidgetItem* parent, const QBrush& brush, int type = QTreeWidgetItem::Type);
	virtual ~WidgetTreeItem() = default;

	inline void setNumb(int column, const QVariant& value)
	{ setData(column, Qt::DisplayRole, value); }

	inline void setId(const QVariant& value)
	{ setData(0, Qt::UserRole, value); }

	void setRating(int column, const QVariant& value);

	void setBold(bool enable);
	void setBackgroundEverywhere(const QBrush& brush);

signals:

};

} // namespace Base
