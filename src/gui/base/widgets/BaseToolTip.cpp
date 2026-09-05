#include "BaseToolTip.h"

#include <QScreen>
#include <QTimer>

Base::ToolTip::ToolTip(QWidget* parent)
	: QLabel{parent}
{
	setWindowFlags(Qt::ToolTip | Qt::FramelessWindowHint);
	setAttribute(Qt::WA_ShowWithoutActivating);
	setAttribute(Qt::WA_TransparentForMouseEvents);
	setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
	setTextFormat(Qt::RichText);
	setMargin(0);
	setStyleSheet(
		"QLabel{"
		"background-color: #ffffff;"
		"color: #000000;"
		"padding: 3px;"
		"}"
	);

	_timer_delay = new QTimer(this);
	_timer_delay->setSingleShot(true);
	connect(_timer_delay, &QTimer::timeout, this, &ToolTip::onTimerDelay);
}

void Base::ToolTip::showText(const QString& text)
{
	if (_show_delay == 0) {
		update(text);
	} else {
		_text = text;
		_timer_delay->start(_show_delay);
	}
}

void Base::ToolTip::hideText()
{
	if (_timer_delay->isActive()) { _timer_delay->stop(); }
	_text.clear();
	hide();
}

void Base::ToolTip::onTimerDelay()
{
	update(_text);
}

void Base::ToolTip::update(const QString& text)
{
	setText(text);
	adjustSize();
	updatePos();
	show();
}

void Base::ToolTip::updatePos()
{
	QPoint pos = QCursor::pos() + QPoint(15, 20);
	QPoint final_pos = pos;
	QScreen* screen = QGuiApplication::screenAt(pos);
	if (screen)
	{
		QRect available = screen->availableGeometry();
		if (final_pos.x() + width() > available.right()) {
			final_pos.setX(pos.x() - width() - 20);
		}
		if (final_pos.y() + height() > available.bottom()) {
			final_pos.setY(pos.y() - height() - 25);
		}
		if (final_pos.x() < available.left()) {
			final_pos.setX(available.left());
		}
		if (final_pos.y() < available.top()) {
			final_pos.setY(available.top());
		}
	}
	move(final_pos);
}
