#include "BaseToolTip.h"

#include <QScreen>

Base::ToolTip::ToolTip(QWidget* parent)
	: QLabel{parent}
{
	setWindowFlags(Qt::ToolTip | Qt::FramelessWindowHint);
	setAttribute(Qt::WA_ShowWithoutActivating);
	setAttribute(Qt::WA_TransparentForMouseEvents);
	setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
	setMargin(0);
	setStyleSheet(
		"QLabel{"
		"background-color: #ffffff;"
		"color: #000000;"
		"padding: 3px;"
		"}"
	);
}

void Base::ToolTip::showText(const QString& text)
{
	setText(text);
	adjustSize();
	updatePos();
	show();
}

void Base::ToolTip::updatePos()
{
	QPoint pos = QCursor::pos() + QPoint(0, 20);
	QPoint final_pos = pos;
	QScreen* screen = QGuiApplication::screenAt(pos);
	if (screen)
	{
		QRect available = screen->availableGeometry();
		if (final_pos.x() + width() > available.right()) {
			final_pos.setX(pos.x() - width());
		}
		if (final_pos.y() + height() > available.bottom()) {
			final_pos.setY(pos.y() - height());
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
