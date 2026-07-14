#include "BaseWidgetSummary.h"

#include <common/Global.h>

#include <QHBoxLayout>
#include <QLabel>

Base::WidgetSummary::WidgetSummary(QWidget* parent)
	: QWidget{parent}
{
	QFont default_font = font();
	default_font.setPointSize(Global::Sizes::font_big);
	setFont(default_font);

	_layout_main = new QHBoxLayout(this);
	_layout_main->setContentsMargins(0, 0, 0, 0);
	_layout_main->setSpacing(Global::Sizes::default_spacing);
}

void Base::WidgetSummary::addWidget(QLabel*& widget, int spacing)
{
	if (widget == nullptr) { widget = new QLabel(this); }
	_layout_main->addWidget(widget);

	addSpacing(spacing);
}

void Base::WidgetSummary::addWidget(const QString& label_text, QLabel*& widget, int spacing)
{
	auto label = new QLabel(label_text, this);
	label->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
	_layout_main->addWidget(label);

	if (widget == nullptr) { widget = new QLabel(this); }
	widget->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	widget->setText("-");
	widget->setStyleSheet(Global::Stylesheets::label_value);
	_layout_main->addWidget(widget);

	addSpacing(spacing);
}

void Base::WidgetSummary::addStretch(int stretch)
{
	_layout_main->addStretch(stretch);
}

void Base::WidgetSummary::addSpacing(int size)
{
	if (size) { _layout_main->addSpacing(size); }
}
