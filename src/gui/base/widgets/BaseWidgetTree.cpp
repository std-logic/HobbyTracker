#include "BaseWidgetTree.h"

#include <QHeaderView>

Base::WidgetTree::WidgetTree(QWidget* parent)
	: QTreeWidget{parent}
{
	setFrameStyle(QFrame::Box);
	setFrameShadow(QFrame::Sunken);
	setLineWidth(1);

	QFont default_font = font();
	default_font.setPointSize(default_font.pointSize() + 2);
	setFont(default_font);

	// keep current sorting column between view modes
	setSortingEnabled(true);
	connect(header(), &QHeaderView::sortIndicatorChanged,
			this, &WidgetTree::sortingChanged);

	hide();
}

void Base::WidgetTree::setViewMode(int view_mode)
{
	if ((view_mode < 0) || (_view_mode == view_mode)) { return; }
	_view_mode = view_mode;
	emit needUpdate();
}

void Base::WidgetTree::clearList()
{
	_sorting_column.clear();

	clear();
	hide();
}

void Base::WidgetTree::initColumns(const QStringList& labels, const std::vector<int>& widths)
{
	setColumnCount(labels.size());
	setHeaderLabels(labels);
	auto head = header();
	head->setStretchLastSection(false);
	for (size_t i = 0; i < widths.size(); ++i) {
		if (widths[i] > 0) {
			head->setSectionResizeMode(i, QHeaderView::Fixed);
			setColumnWidth(i, widths[i]);
		} else {
			head->setStretchLastSection(false);
			head->setSectionResizeMode(i, QHeaderView::Stretch);
		}
	}
}

void Base::WidgetTree::initSorting(int default_column, Qt::SortOrder default_order)
{
	auto header_item = headerItem();
	for (int column = 0; column < columnCount(); ++column) {
		if (header_item->text(column) == _sorting_column) {
			sortByColumn(column, _sorting_order);
			return;
		}
	}
	sortByColumn(default_column, default_order);
}

void Base::WidgetTree::sortingChanged(int index, Qt::SortOrder order)
{
	if (index == -1) { return; }
	_sorting_column = headerItem()->text(index);
	_sorting_order = order;
}
