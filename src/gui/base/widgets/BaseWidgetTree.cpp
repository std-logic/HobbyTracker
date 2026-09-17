#include "BaseWidgetTree.h"
#include "BaseWidgetTreeItem.h"
#include "BaseToolTip.h"

#include <common/Global.h>

#include <QHeaderView>
#include <QShortcut>
#include <QMouseEvent>
#include <QDesktopServices>

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

	setIconSize(QSize(24, 16));

	// keep current sorting column between view modes
	setSortingEnabled(true);
	connect(header(), &QHeaderView::sortIndicatorChanged,
			this, &WidgetTree::sortingChanged);

	// tracking items doubleclicking
	connect(this, &WidgetTree::itemDoubleClicked,
			this, &WidgetTree::onItemDoubleClicked);

	// tracking items expanding/collapsing
	connect(this, &WidgetTree::itemExpanded,
			this, &WidgetTree::onItemExpanded);
	connect(this, &WidgetTree::itemCollapsed,
			this, &WidgetTree::onItemCollapsed);

	// tracking items delete pressing
	auto shortcut = new QShortcut(QKeySequence(Qt::Key_Delete), this);
	shortcut->setContext(Qt::WidgetShortcut);
	connect(shortcut, &QShortcut::activated,
			this, &WidgetTree::onItemDeletePressed);

	// tracking mouse for hovered tooltip processing
	setMouseTracking(true);

	_tooltip = new ToolTip(this);
	_tooltip->setShowDelay(300);

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

void Base::WidgetTree::findText(const QString& search_text)
{
	_search_text = search_text;
	for (int i = 0; i < topLevelItemCount(); ++i) {
		filterItem(topLevelItem(i), search_text);
	}
}

void Base::WidgetTree::setSearchColumns(const std::vector<int>& columns)
{
	_search_columns = columns;
}

void Base::WidgetTree::updateSearch()
{
	if (!_search_text.isEmpty()) {
		findText(_search_text);
	}
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
	auto head_item = headerItem();
	for (int i = 0; i < head_item->columnCount(); ++i) {
		head_item->setIcon(i, QIcon());
	}
}

void Base::WidgetTree::initSorting(int default_column, Qt::SortOrder default_order, bool force)
{
	if (!force && !_sorting_column.isEmpty()) {
		auto header_item = headerItem();
		for (int column = 0; column < columnCount(); ++column) {
			if (header_item->text(column) == _sorting_column) {
				sortByColumn(column, _sorting_order);
				return;
			}
		}
	}
	sortByColumn(default_column, default_order);
}

void Base::WidgetTree::initPhotoColumn(int column)
{
	auto head_item = headerItem();
	head_item->setIcon(column, QIcon::fromTheme(QIcon::ThemeIcon::CameraPhoto));
}

void Base::WidgetTree::mousePressEvent(QMouseEvent* event)
{
	hideToolTip();

	const QPoint pos = event->position().toPoint();
	QTreeWidgetItem* item = itemAt(pos);

	if (item) {
		if (event->button() == Qt::RightButton) {
			showRightClickToolTip(item);
		} else if (event->button() == Qt::LeftButton) {
			int column = columnAt(pos.x());
			openLink(item, column);
		}
	}

	QTreeWidget::mousePressEvent(event);
}

void Base::WidgetTree::mouseMoveEvent(QMouseEvent* event)
{
	const QPoint pos = event->position().toPoint();
	QTreeWidgetItem* item = itemAt(pos);
	int column = columnAt(pos.x());
	bool item_changed = false, column_changed = false;

	if (_hovered_item != item) {
		if (_hovered_item) { hideToolTip(); }
		_hovered_item = item;
		if (_hovered_item) { showHoveredToolTip(_hovered_item); }
		item_changed = true;
	}

	if (_hovered_column != column) {
		_hovered_column = column;
		column_changed = true;
	}

	if (item_changed || column_changed) {
		showLinkCursor(_hovered_item, _hovered_column);
	}

	QTreeWidget::mouseMoveEvent(event);
}

void Base::WidgetTree::leaveEvent(QEvent* event)
{
	hideToolTip();
	hideLinkCursor();
	_hovered_item = nullptr;
	_hovered_column = -1;

	QTreeWidget::leaveEvent(event);
}

void Base::WidgetTree::showHoveredToolTip(QTreeWidgetItem* item)
{
	auto base_item = dynamic_cast<WidgetTreeItem*>(item);
	if (base_item && base_item->hasHoveredToolTip()) {
		_tooltip->showText(base_item->hoveredToolTip(), base_item->hoveredMode());
	}
}

void Base::WidgetTree::showRightClickToolTip(QTreeWidgetItem* item)
{
	auto base_item = dynamic_cast<WidgetTreeItem*>(item);
	if (base_item && base_item->hasRightClickToolTip()) {
		_tooltip->showText(base_item->rightClickToolTip(), base_item->rightClickMode(), true);
	}
}

void Base::WidgetTree::hideToolTip()
{
	_tooltip->hideText();
}

void Base::WidgetTree::showLinkCursor(QTreeWidgetItem* item, int column)
{
	auto base_item = dynamic_cast<WidgetTreeItem*>(item);
	if (base_item && base_item->hasPhotoLink(column)) {
		viewport()->setCursor(Qt::PointingHandCursor);
	} else {
		viewport()->unsetCursor();
	}
}

void Base::WidgetTree::hideLinkCursor()
{
	viewport()->unsetCursor();
}

void Base::WidgetTree::openLink(QTreeWidgetItem* item, int column)
{
	auto base_item = dynamic_cast<WidgetTreeItem*>(item);
	if (base_item && base_item->hasPhotoLink(column)) {
		QDesktopServices::openUrl(QUrl::fromLocalFile(base_item->photoLink()));
	}
}

bool Base::WidgetTree::filterItem(QTreeWidgetItem* item,
		const QString& search_text, bool parent_found)
{
	bool self_found = search_text.isEmpty() || parent_found;
	if (!self_found) {
		for (auto clmn : _search_columns) {
			if (item->text(clmn).contains(search_text, Qt::CaseInsensitive)) {
				self_found = true;
				break;
			}
		}
	}

	bool child_found = false;
	for (int i = 0; i < item->childCount(); ++i) {
		if (filterItem(item->child(i), search_text, self_found)) {
			child_found = true;
		}
	}

	bool visible = self_found || child_found;
	item->setHidden(!visible);

	return visible;
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

void Base::WidgetTree::onItemExpanded(QTreeWidgetItem* /*item*/)
{
	hideToolTip();
}

void Base::WidgetTree::onItemCollapsed(QTreeWidgetItem* /*item*/)
{
	hideToolTip();
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
