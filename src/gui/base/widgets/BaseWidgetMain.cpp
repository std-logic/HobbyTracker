#include "BaseWidgetMain.h"

#include <common/Global.h>

#include <QVBoxLayout>
#include <QMessageBox>

Base::WidgetMain::WidgetMain(QWidget* parent)
	: QWidget{parent}
{
	_layout_main = new QVBoxLayout(this);
	_layout_main->setContentsMargins(Global::Sizes::default_margin);
	_layout_main->setSpacing(Global::Sizes::default_spacing);
}

void Base::WidgetMain::addWidget(QWidget* widget, int stretch, Qt::Alignment alignment)
{
	_layout_main->addWidget(widget, stretch, alignment);
}

void Base::WidgetMain::addStretch(int stretch)
{
	_layout_main->addStretch(stretch);
}

bool Base::WidgetMain::ask(const QString& title, const QString& text)
{
	return (QMessageBox::question(this, title, text) == QMessageBox::Yes);
}
