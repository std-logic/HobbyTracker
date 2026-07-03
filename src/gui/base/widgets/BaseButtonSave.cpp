#include "BaseButtonSave.h"

#include <common/Global.h>

Base::ButtonSave::ButtonSave(QWidget* parent)
	: QPushButton{tr("Сохранить"), parent}
{
}

void Base::ButtonSave::highlight(bool on)
{
	setStyleSheet(on ? Global::Stylesheets::button_highligh : "");
}
