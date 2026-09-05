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

	void setCountry(int column, const QString& country);

	void setBold(int column, bool enable);
	void setBoldEverywhere(bool enable);
	void setBackgroundEverywhere(const QBrush& brush);

	void setCustomToolTip(const QString& str) { _custom_tooltip = str; }
	bool hasCustomToolTip() const { return !_custom_tooltip.isEmpty(); }
	QString customToolTip() const { return _custom_tooltip; }

private:
	QString _custom_tooltip;
};

} // namespace Base
