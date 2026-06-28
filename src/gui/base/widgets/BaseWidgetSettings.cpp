#include "BaseWidgetSettings.h"

#include <common/Global.h>

#include <QGridLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>

Base::WidgetSettings::WidgetSettings(QWidget* parent)
	: QDialog{parent}
{
	initCommonParams();
	initWidgets();
}

void Base::WidgetSettings::addWidget(QWidget* widget)
{
	_layout_main->addWidget(widget, _layout_main->rowCount(), 0, 1, 2);
}

void Base::WidgetSettings::addWidget(const QString& label_text, QWidget* widget)
{
	auto row_count = _layout_main->rowCount();
	auto label = new QLabel(label_text, this);
	label->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
	_layout_main->addWidget(label, row_count, 0);
	_layout_main->addWidget(widget, row_count, 1);
}

void Base::WidgetSettings::addLayout(QLayout* layout)
{
	_layout_main->addLayout(layout, _layout_main->rowCount(), 0, 1, 2);
}

void Base::WidgetSettings::addLayout(const QString& label_text, QLayout* layout)
{
	auto row_count = _layout_main->rowCount();
	auto label = new QLabel(label_text, this);
	label->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
	_layout_main->addWidget(label, row_count, 0);
	_layout_main->addLayout(layout, row_count, 1);
}

void Base::WidgetSettings::addStandardButtons()
{
	auto row_count = _layout_main->rowCount();

	_button_save = new QPushButton(tr("Сохранить"), this);
	connect(_button_save, &QPushButton::clicked,
			this, &WidgetSettings::save);
	_layout_main->addWidget(_button_save, row_count, 0);

	_button_exit = new QPushButton(tr("Закрыть"), this);
	connect(_button_exit, &QPushButton::clicked,
			this, &WidgetSettings::close);
	_layout_main->addWidget(_button_exit, row_count, 1);
}

void Base::WidgetSettings::initCommonParams()
{
	setAttribute(Qt::WA_DeleteOnClose);
	setWindowTitle(tr("Настройки"));
	setMinimumWidth(300);
}

void Base::WidgetSettings::initWidgets()
{
	_layout_main = new QGridLayout(this);
	_layout_main->setContentsMargins(Global::Sizes::default_margin);
	_layout_main->setSpacing(Global::Sizes::default_spacing);
	_layout_main->setColumnStretch(0, 50);
	_layout_main->setColumnStretch(1, 50);
}
