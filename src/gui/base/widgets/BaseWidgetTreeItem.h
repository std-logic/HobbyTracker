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

	void setHoveredToolTip(const QString& str) { _hovered_tooltip = str; }
	bool hasHoveredToolTip() const { return !_hovered_tooltip.isEmpty(); }
	QString hoveredToolTip() const { return _hovered_tooltip; }

	void setRightClickToolTip(const QString& str) { _rightclick_tooltip = str; }
	bool hasRightClickToolTip() const { return !_rightclick_tooltip.isEmpty(); }
	QString rightClickToolTip() const { return _rightclick_tooltip; }

private:
	QString _hovered_tooltip;
	QString _rightclick_tooltip;
};

} // namespace Base
