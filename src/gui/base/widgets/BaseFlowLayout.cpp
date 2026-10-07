#include "BaseFlowLayout.h"

#include <common/Global.h>

#include <QtWidgets>

Base::FlowLayout::FlowLayout(QWidget* parent)
	: QLayout{parent}
{
	setContentsMargins(0, 0, 0, 0);
	setSpacing(Global::Sizes::default_spacing);
}

void Base::FlowLayout::addItem(QLayoutItem* item)
{
	_items.append(item);
}

void Base::FlowLayout::insertWidget(int index, QWidget* widget)
{
	if ((index < 0) || !widget) { return; }

	if (index > _items.size()) {
		index = _items.size();
	}

	_items.insert(index, new QWidgetItem(widget));
	widget->show();
	invalidate();
}

void Base::FlowLayout::changeWidget(int index, QWidget* widget)
{
	if ((index < 0) || (index >= _items.size()) || !widget) { return; }

	auto item = _items.takeAt(index);
	delete item->widget();
	delete item;

	insertWidget(index, widget);
}

void Base::FlowLayout::moveWidget(int from, int to)
{
	_items.move(from, to);
	invalidate();
}

QLayoutItem* Base::FlowLayout::itemAt(int index) const
{
	return _items.value(index);
}

QLayoutItem* Base::FlowLayout::takeAt(int index)
{
	return ((0 <= index) && (index < _items.size())) ? _items.takeAt(index) : nullptr;
}

int Base::FlowLayout::count() const
{
	return _items.size();
}

Qt::Orientations Base::FlowLayout::expandingDirections() const
{
	return {};
}

bool Base::FlowLayout::hasHeightForWidth() const
{
	return true;
}

int Base::FlowLayout::heightForWidth(int width) const
{
	return doLayout(QRect(0, 0, width, 0), true);
}

QSize Base::FlowLayout::sizeHint() const
{
	return minimumSize();
}

QSize Base::FlowLayout::minimumSize() const
{
	QSize size;
	for (const auto* item : _items) {
		size = size.expandedTo(item->minimumSize());
	}
	return size;
}

void Base::FlowLayout::setGeometry(const QRect& rect)
{
	QLayout::setGeometry(rect);
	doLayout(rect, false);
}

int Base::FlowLayout::doLayout(const QRect& rect, bool test_only) const
{
	int x = rect.x();
	int y = rect.y();
	int line_height = 0;
	int space = spacing();
	int right = rect.x() + rect.width();

	for (auto* item : _items) {
		QSize item_size = item->sizeHint();
		if (((x + item_size.width()) > right) && (line_height > 0)) {
			x = rect.x();
			y += line_height + space;
			line_height = 0;
		}

		if (!test_only) {
			item->setGeometry(QRect(x, y, item_size.width(), item_size.height()));
		}

		x += item_size.width() + space;
		line_height = qMax(line_height, item_size.height());
	}

	return y - rect.y() + line_height;
}
