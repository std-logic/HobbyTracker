#pragma once

#include "BaseToolTip.h"

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

	void setPhotoLink(int column, const QString& photo_dir, const QString& photo_link);
	bool hasPhotoLink(int column) const { return (_photo_column == column); }
	QString photoLink() const { return _photo_link; }

	void setBold(int column, bool enable);
	void setBoldEverywhere(bool enable);
	void setBackgroundEverywhere(const QBrush& brush);

	void setHoveredToolTip(const QString& str, ToolTip::Mode mode = ToolTip::Mode::Text)
	{ _hovered_tooltip = str; _hovered_mode = mode; }
	bool hasHoveredToolTip() const { return !_hovered_tooltip.isEmpty(); }
	QString hoveredToolTip() const { return _hovered_tooltip; }
	ToolTip::Mode hoveredMode() const { return _hovered_mode; }

	void setRightClickToolTip(const QString& str, ToolTip::Mode mode = ToolTip::Mode::Text)
	{ _rightclick_tooltip = str; _rightclick_mode = mode; }
	bool hasRightClickToolTip() const { return !_rightclick_tooltip.isEmpty(); }
	QString rightClickToolTip() const { return _rightclick_tooltip; }
	ToolTip::Mode rightClickMode() const { return _rightclick_mode; }

private:
	QString _hovered_tooltip;
	ToolTip::Mode _hovered_mode = ToolTip::Mode::Text;

	QString _rightclick_tooltip;
	ToolTip::Mode _rightclick_mode = ToolTip::Mode::Text;

	int _photo_column = -1;
	QString _photo_link;
};

} // namespace Base
