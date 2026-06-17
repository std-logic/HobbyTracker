#include "BaseWidgetControl.h"

#include <QHBoxLayout>

Base::WidgetControl::WidgetControl(QWidget* parent)
	: QWidget{parent}
{
	_main_layout = new QHBoxLayout(this);
	_main_layout->setContentsMargins(0, 0, 0, 0);
	_main_layout->setSpacing(5);
}

void Base::WidgetControl::addWidget(QWidget* widget, int stretch, Qt::Alignment alignment)
{
	_main_layout->addWidget(widget, stretch, alignment);
}

void Base::WidgetControl::addStretch(int stretch)
{
	_main_layout->addStretch(stretch);
}

void Base::WidgetControl::addSpacing(int size)
{
	_main_layout->addSpacing(size);
}
