#pragma once

#include <QTreeWidget>

namespace Base
{

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
	void initSorting(int default_column = 0, Qt::SortOrder default_order = Qt::AscendingOrder);

private slots:
	void sortingChanged(int index, Qt::SortOrder order);
	void onItemDoubleClicked(QTreeWidgetItem* item, int column);
	void onItemDeletePressed();

protected:
	int _view_mode = 0;

	QString _sorting_column;
	Qt::SortOrder _sorting_order = Qt::AscendingOrder;
};

} // namespace Base
