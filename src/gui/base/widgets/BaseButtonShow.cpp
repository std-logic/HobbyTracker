#include "BaseButtonShow.h"

Base::ButtonShow::ButtonShow(const QString& text, QWidget* parent)
	: QPushButton{text, parent}
{
	setCheckable(true);
	setFlat(true);
}
