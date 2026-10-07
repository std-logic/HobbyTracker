#include "BaseFlowItem.h"
#include "BaseFlowMimeData.h"

#include <common/Global.h>

#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QDrag>
#include <QMouseEvent>
#include <QApplication>
#include <QWindow>

Base::FlowItem::FlowItem(QWidget* parent)
	: QFrame{parent}
{
	initCommonParams();
	initWidgets();
}

void Base::FlowItem::addWidget(QWidget* widget)
{
	_layout_main->insertWidget(0, widget, 1);
	disableChildDrops(widget);
}

QWidget* Base::FlowItem::widget() const
{
	return _layout_main->itemAt(0)->widget();
}

void Base::FlowItem::mousePressEvent(QMouseEvent* event)
{
	if ((event->button() == Qt::LeftButton) &&
		_label_drag->geometry().contains(event->pos())) {
		_drag_start_pos = event->pos();
		_drag_started = true;
	} else {
		_drag_started = false;
	}

	QWidget::mousePressEvent(event);
}

void Base::FlowItem::mouseMoveEvent(QMouseEvent* event)
{
	if (!(event->buttons() & Qt::LeftButton)) { return; }
	if (!_drag_started) { return; }
	int drag_dist = (event->pos() - _drag_start_pos).manhattanLength();
	if (drag_dist < QApplication::startDragDistance()) { return; }

	qreal dpr = window()->windowHandle()->devicePixelRatio();
	QPixmap pixmap(size() * dpr);
	pixmap.setDevicePixelRatio(dpr);
	pixmap.fill(Qt::transparent);
	render(&pixmap);

	auto* mime_data = new FlowMimeData;
	mime_data->widget = this;

	auto* drag = new QDrag(this);
	drag->setMimeData(mime_data);
	drag->setPixmap(pixmap);
	drag->setHotSpot(_drag_start_pos);
	drag->exec(Qt::MoveAction);
}

void Base::FlowItem::initCommonParams()
{
	setFixedHeight(30);
	setStyleSheet(
		"QFrame{"
		"background-color: rgb(220,220,220);"
		"border: 1px solid rgb(210,210,210);"
		"border-radius: 3px;"
		"padding-left: 2px;"
		"padding-right: 2px;"
		"padding-top: 2px;"
		"padding-bottom: 2px;"
		"}"
	);
}

void Base::FlowItem::initWidgets()
{
	_layout_main = new QHBoxLayout(this);
	_layout_main->setContentsMargins(0, 0, 0, 0);
	_layout_main->setSpacing(2);

	_button_del = new QPushButton("✕", this);
	_button_del->setToolTip(tr("Удалить"));
	_button_del->setFixedSize(16, 16);
	connect(_button_del, &QPushButton::clicked, this, [this](){
		emit delWidget(this);
	});
	_layout_main->addWidget(_button_del);

	_label_drag = new QLabel("||", this);
	_label_drag->setAlignment(Qt::AlignCenter);
	_label_drag->setStyleSheet(
		"QLabel{"
		"background-color: rgb(220,220,220);"
		"color: rgb(130,130,130);"
		"border: 0px;"
		"padding-left: 2px;"
		"padding-right: 2px;"
		"padding-top: 0px;"
		"padding-bottom: 4px;"
		"font-size: 12pt;"
		"}"
	);
	_layout_main->addWidget(_label_drag);
}

void Base::FlowItem::disableChildDrops(QWidget* widget)
{
	widget->setAcceptDrops(false);
	for (QWidget* child : widget->findChildren<QWidget*>()) {
		child->setAcceptDrops(false);
	}
}
