#include "BaseButtonCollapse.h"

Base::ButtonCollapse::ButtonCollapse(QWidget* parent)
	: QPushButton{QIcon::fromTheme(QIcon::ThemeIcon::GoUp), QStringLiteral(""), parent}
{
	setToolTip(tr("Свернуть всё"));
	setFixedWidth(24);
}
