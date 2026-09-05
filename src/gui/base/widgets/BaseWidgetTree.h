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

signals:
	void needUpdate();
	void editData(const QString& id);
	void deleteData(const QString& id);

protected:
	void initColumns(const QStringList& labels, const std::vector<int>& widths = {});
	void initSorting(int default_column = 0, Qt::SortOrder default_order = Qt::AscendingOrder, bool force = false);

	void mouseMoveEvent(QMouseEvent* event) override;
	void leaveEvent(QEvent* event) override;

private:
	void showToolTip();
	void hideToolTip();

private slots:
	void sortingChanged(int index, Qt::SortOrder order);
	void onItemDoubleClicked(QTreeWidgetItem* item, int column);
	void onItemDeletePressed();

protected:
	int _view_mode = 0;

	QString _sorting_column;
	Qt::SortOrder _sorting_order = Qt::AscendingOrder;

	QTreeWidgetItem* _hovered_item = nullptr;
	Base::ToolTip* _tooltip = nullptr;
};

} // namespace Base
