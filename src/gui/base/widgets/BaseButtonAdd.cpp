#include "BaseButtonAdd.h"

Base::ButtonAdd::ButtonAdd(QWidget* parent)
	: QPushButton{QIcon::fromTheme(QIcon::ThemeIcon::ListAdd), QStringLiteral(""), parent}
{
	setToolTip(tr("Добавить..."));
	setFixedWidth(24);
}
