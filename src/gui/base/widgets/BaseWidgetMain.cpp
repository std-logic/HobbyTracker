#include "BaseWidgetMain.h"

#include <QVBoxLayout>

Base::WidgetMain::WidgetMain(QWidget* parent)
	: QWidget{parent}
{
	_main_layout = new QVBoxLayout(this);
	_main_layout->setContentsMargins(5, 5, 5, 5);
	_main_layout->setSpacing(5);
}

void Base::WidgetMain::addWidget(QWidget* widget, int stretch, Qt::Alignment alignment)
{
	_main_layout->addWidget(widget, stretch, alignment);
}

void Base::WidgetMain::addStretch(int stretch)
{
	_main_layout->addStretch(stretch);
}
