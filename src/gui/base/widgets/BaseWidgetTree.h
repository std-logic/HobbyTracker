#pragma once

#include <QTreeWidget>

namespace Base
{

class ToolTip;

class WidgetTree : public QTreeWidget
{
	Q_OBJECT
public:
	explicit WidgetTree(QWidget* parent = nullptr);
	virtual ~WidgetTree() = default;

public slots:
	virtual void setViewMode(int view_mode);
	virtual void clearList();
	void findText(const QString& search_text);

signals:
	void needUpdate();
	void editData(const QString& id);
	void deleteData(const QString& id);

protected:
	void setSearchColumns(const std::vector<int>& columns);
	void updateSearch();
	void initColumns(const QStringList& labels, const std::vector<int>& widths = {});
	void initSorting(int default_column = 0, Qt::SortOrder default_order = Qt::AscendingOrder, bool force = false);

	void mousePressEvent(QMouseEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;
	void leaveEvent(QEvent* event) override;

private:
	void showHoveredToolTip(QTreeWidgetItem* item);
	void showRightClickToolTip(QTreeWidgetItem* item);
	void hideToolTip();
	bool filterItem(QTreeWidgetItem* item, const QString& search_text, bool parent_found = false);

private slots:
	void sortingChanged(int index, Qt::SortOrder order);
	void onItemDoubleClicked(QTreeWidgetItem* item, int column);
	void onItemExpanded(QTreeWidgetItem* item);
	void onItemCollapsed(QTreeWidgetItem* item);
	void onItemDeletePressed();

protected:
	int _view_mode = 0;

	QString _sorting_column;
	Qt::SortOrder _sorting_order = Qt::AscendingOrder;

	QTreeWidgetItem* _hovered_item = nullptr;
	Base::ToolTip* _tooltip = nullptr;

	std::vector<int> _search_columns;
	QString _search_text;
};

} // namespace Base
