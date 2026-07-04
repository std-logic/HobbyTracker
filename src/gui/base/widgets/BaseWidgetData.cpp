#include "BaseWidgetData.h"

#include <common/Global.h>

#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>

Base::WidgetData::WidgetData(QWidget* parent)
	: QDialog{parent}
{
	initCommonParams();
	initWidgets();
}

void Base::WidgetData::addWidget(QWidget* widget)
{
	_layout_main->addWidget(widget, _layout_main->rowCount(), 0, 1, 2);
}

void Base::WidgetData::addWidget(const QString& label_text, QWidget* widget)
{
	auto row_count = _layout_main->rowCount();
	auto label = new QLabel(label_text, this);
	label->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
	_layout_main->addWidget(label, row_count, 0);
	_layout_main->addWidget(widget, row_count, 1);
}

void Base::WidgetData::addLayout(QLayout* layout)
{
	_layout_main->addLayout(layout, _layout_main->rowCount(), 0, 1, 2);
}

void Base::WidgetData::addLayout(const QString& label_text, QLayout* layout)
{
	auto row_count = _layout_main->rowCount();
	auto label = new QLabel(label_text, this);
	label->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
	_layout_main->addWidget(label, row_count, 0);
	_layout_main->addLayout(layout, row_count, 1);
}

void Base::WidgetData::initCommonParams()
{
	setAttribute(Qt::WA_DeleteOnClose);
	setWindowTitle(tr("Данные"));
	setMinimumWidth(400);
}

void Base::WidgetData::initWidgets()
{
	auto layout_top = new QVBoxLayout(this);
	layout_top->setContentsMargins(Global::Sizes::default_margin);
	layout_top->setSpacing(Global::Sizes::default_spacing);

	_layout_main = new QGridLayout();
	_layout_main->setContentsMargins(0, 0, 0, 0);
	_layout_main->setSpacing(Global::Sizes::default_spacing);

	layout_top->addLayout(_layout_main);

	auto layout_buttons = new QHBoxLayout();
	layout_buttons->setContentsMargins(0, 0, 0, 0);
	layout_buttons->setSpacing(Global::Sizes::default_spacing);

	_button_save = new QPushButton(tr("OK"), this);
	connect(_button_save, &QPushButton::clicked,
			this, &WidgetData::save);
	layout_buttons->addWidget(_button_save);

	_button_exit = new QPushButton(tr("Отмена"), this);
	connect(_button_exit, &QPushButton::clicked,
			this, &WidgetData::close);
	layout_buttons->addWidget(_button_exit);

	layout_top->addLayout(layout_buttons);
}
