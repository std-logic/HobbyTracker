#include "BaseWidgetControl.h"
#include "BaseButtonSave.h"
#include "BaseButtonSettings.h"

#include <common/Global.h>

#include <QHBoxLayout>

Base::WidgetControl::WidgetControl(QWidget* parent)
	: QWidget{parent}
{
	_layout_main = new QHBoxLayout(this);
	_layout_main->setContentsMargins(0, 0, 0, 0);
	_layout_main->setSpacing(Global::Sizes::default_spacing);
}

void Base::WidgetControl::highlightButtonSave(bool on)
{
	if (_button_save) { _button_save->highlight(on); }
}

void Base::WidgetControl::addWidget(QWidget* widget, int stretch, Qt::Alignment alignment)
{
	_layout_main->addWidget(widget, stretch, alignment);
}

void Base::WidgetControl::addStretch(int stretch)
{
	_layout_main->addStretch(stretch);
}

void Base::WidgetControl::addSpacing(int size)
{
	_layout_main->addSpacing(size);
}

void Base::WidgetControl::addButtonSave()
{
	addWidget(_button_save = new ButtonSave(this));
	connect(_button_save, &ButtonSave::clicked,
			this, &WidgetControl::saveCsvData);
}

void Base::WidgetControl::addButtonSettings()
{
	addStretch();

	addWidget(_button_settings = new ButtonSettings(this));
	connect(_button_settings, &ButtonSettings::clicked,
			this, &WidgetControl::showSettings);
}
