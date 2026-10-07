#include "BaseFlowContainer.h"
#include "BaseFlowLayout.h"
#include "BaseFlowItem.h"
#include "BaseFlowPlaceholder.h"

#include <common/Global.h>

#include <QHBoxLayout>
#include <QPushButton>
#include <QDragEnterEvent>
#include <QDragLeaveEvent>
#include <QDragMoveEvent>
#include <QDropEvent>
#include <QMimeData>

Base::FlowContainer::FlowContainer(QWidget* parent)
	: QWidget{parent}
{
	initCommonParams();
	initWidgets();
}

int Base::FlowContainer::count() const
{
	return _layout_flow->count();
}

QWidget* Base::FlowContainer::widgetAt(int index) const
{
	return dynamic_cast<Base::FlowItem*>(_layout_flow->itemAt(index)->widget())->widget();
}

void Base::FlowContainer::addWidget(FlowItem* widget)
{
	connect(widget, &FlowItem::delWidget, this, &FlowContainer::delWidget);
	widget->setFixedWidth(_fixed_item_width);
	_layout_flow->addWidget(widget);
	_layout_flow->invalidate();
	scheduleHeightAdjustment();
}

void Base::FlowContainer::delWidget(QWidget* widget)
{
	_layout_flow->removeWidget(widget);
	widget->deleteLater();
	_layout_flow->invalidate();
	scheduleHeightAdjustment();
}

void Base::FlowContainer::dragEnterEvent(QDragEnterEvent* event)
{
	auto* widget = widgetFromMimeData(event->mimeData());
	if (!widget) { return; }
	if (widget->parentWidget() != this) { return; }
	if (_dragged_widget) { return; }

	startDragging(widget);

	event->setDropAction(Qt::MoveAction);
	event->accept();
}

void Base::FlowContainer::dragMoveEvent(QDragMoveEvent* event)
{
	if (!_dragged_widget || !_placeholder_widget) {
		event->ignore();
		return;
	}

	auto position = event->position().toPoint();
	position -= QPoint(_placeholder_widget->width()/2, 0);
	movePlaceholder(position);

	event->setDropAction(Qt::MoveAction);
	event->accept();
}

void Base::FlowContainer::dragLeaveEvent(QDragLeaveEvent* event)
{
	finishDragging();

	event->accept();
}

void Base::FlowContainer::dropEvent(QDropEvent* event)
{
	if (!_dragged_widget || !_placeholder_widget) {
		event->ignore();
		return;
	}

	finishDragging();

	event->setDropAction(Qt::MoveAction);
	event->accept();
}

void Base::FlowContainer::initCommonParams()
{
	setAcceptDrops(true);
}

void Base::FlowContainer::initWidgets()
{
	_layout_main = new QHBoxLayout(this);
	_layout_main->setContentsMargins(0, 0, 0, 0);
	_layout_main->setSpacing(Global::Sizes::default_spacing);

	_layout_flow = new FlowLayout();
	_layout_main->addLayout(_layout_flow, 1);

	_button_add = new QPushButton(QIcon::fromTheme(QIcon::ThemeIcon::ListAdd), "", this);
	_button_add->setToolTip(tr("Добавить"));
	_button_add->setFixedWidth(24);
	_button_add->setMinimumHeight(30);
	_button_add->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
	connect(_button_add, &QPushButton::clicked, this, &FlowContainer::addWidgetRequest);
	_layout_main->addWidget(_button_add);
}

Base::FlowItem* Base::FlowContainer::widgetFromMimeData(const QMimeData* mime_data) const
{
	auto* flow_mime_data = dynamic_cast<const FlowMimeData*>(mime_data);
	if (flow_mime_data && flow_mime_data->widget) {
		return flow_mime_data->widget;
	}
	return nullptr;
}

int Base::FlowContainer::indexFromPosition(const QPoint& position) const
{
	for (int i = 0; i < _layout_flow->count(); ++i) {
		auto item = _layout_flow->itemAt(i);
		if (!item) { continue; }
		auto widget = item->widget();
		if (widget && widget->geometry().contains(position)) {
			return i;
		}
	}
	return -1;
}

void Base::FlowContainer::startDragging(FlowItem* widget)
{
	int index = _layout_flow->indexOf(widget);
	if (index < 0) { return; }

	auto item = _layout_flow->takeAt(index);
	delete item;

	_dragged_widget = widget;
	_dragged_widget->hide();

	_placeholder_index = index;
	_placeholder_widget = new FlowPlaceholder(_dragged_widget->size(), this);
	_layout_flow->insertWidget(_placeholder_index, _placeholder_widget);
}

void Base::FlowContainer::movePlaceholder(const QPoint& position)
{
	int new_index = indexFromPosition(position);
	if ((new_index >= 0) && (new_index != _placeholder_index)) {
		_layout_flow->moveWidget(_placeholder_index, new_index);
		_placeholder_index = new_index;
	}
}

void Base::FlowContainer::finishDragging()
{
	_layout_flow->changeWidget(_placeholder_index, _dragged_widget);

	_dragged_widget = nullptr;
	_placeholder_widget = nullptr;
	_placeholder_index = -1;
}

void Base::FlowContainer::scheduleHeightAdjustment()
{
	if (_adjust_window_height_scheduled) { return; }
	_adjust_window_height_scheduled = true;

	QMetaObject::invokeMethod(this, &FlowContainer::adjustWindowHeight, Qt::QueuedConnection);
}

void Base::FlowContainer::adjustWindowHeight()
{
	_adjust_window_height_scheduled = false;

	int old_height = height();
	int flow_width = _layout_flow->geometry().width();
	int new_height = _layout_flow->heightForWidth(flow_width);
	if (old_height != new_height) {
		window()->resize(window()->width(), window()->height() + new_height - old_height);
	}
}
