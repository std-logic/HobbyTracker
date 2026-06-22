#include "BaseButtonExpand.h"

Base::ButtonExpand::ButtonExpand(QWidget* parent)
	: QPushButton{QIcon::fromTheme(QIcon::ThemeIcon::GoDown), QStringLiteral(""), parent}
{
	setToolTip(tr("Развернуть всё"));
	setFixedWidth(24);
}
