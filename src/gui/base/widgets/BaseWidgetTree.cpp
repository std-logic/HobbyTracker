#include "BaseWidgetTree.h"

#include <common/Global.h>

#include <QHeaderView>
#include <QShortcut>

Base::WidgetTree::WidgetTree(QWidget* parent)
	: QTreeWidget{parent}
{
	setFrameStyle(QFrame::Box);
	setFrameShadow(QFrame::Sunken);
	setLineWidth(1);

	setStyleSheet(Global::Stylesheets::tree_widget);

	QFont default_font = font();
	default_font.setPointSize(Global::Sizes::font_big);
	setFont(default_font);

	// keep current sorting column between view modes
	setSortingEnabled(true);
	connect(header(), &QHeaderView::sortIndicatorChanged,
			this, &WidgetTree::sortingChanged);

	// tracking items doubleclicking
	connect(this, &WidgetTree::itemDoubleClicked,
			this, &WidgetTree::onItemDoubleClicked);

	// tracking items delete pressing
	auto shortcut = new QShortcut(QKeySequence(Qt::Key_Delete), this);
	shortcut->setContext(Qt::WidgetShortcut);
	connect(shortcut, &QShortcut::activated,
			this, &WidgetTree::onItemDeletePressed);

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

void Base::WidgetTree::onItemDoubleClicked(QTreeWidgetItem* item, int /*column*/)
{
	auto id = item->data(0, Qt::UserRole).toString();
	if (!id.isEmpty()) {
		emit editData(id);
	}
}

void Base::WidgetTree::onItemDeletePressed()
{
	auto item = currentItem();
	if (item) {
		auto id = item->data(0, Qt::UserRole).toString();
		if (!id.isEmpty()) {
			emit deleteData(id);
		}
	}
}
