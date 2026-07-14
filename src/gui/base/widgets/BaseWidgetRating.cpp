#include "BaseWidgetRating.h"

#include <QHBoxLayout>
#include <QPushButton>
#include <QButtonGroup>

Base::WidgetRating::WidgetRating(QWidget* parent)
	: QWidget{parent}
{
	initWidgets();
}

void Base::WidgetRating::setRating(uint32_t rating)
{
	if ((1 <= rating) && (rating <= 10)) {
		_group_buttons->button(rating)->setChecked(true);
	} else {
		// dirty trick for uncheck all buttons
		_group_buttons->setExclusive(false);
		if (auto* button = _group_buttons->checkedButton()) {
			button->setChecked(false);
		}
		_group_buttons->setExclusive(true);
	}
}

uint32_t Base::WidgetRating::rating() const
{
	auto id = _group_buttons->checkedId();
	return (id < 0) ? 0 : id;
}

bool Base::WidgetRating::isValid() const
{
	auto r = rating();
	return (1 <= r) && (r <= 10);
}

void Base::WidgetRating::initWidgets()
{
	_layout_main = new QHBoxLayout(this);
	_layout_main->setContentsMargins(0, 0, 0, 0);
	_layout_main->setSpacing(1);

	_group_buttons = new QButtonGroup(this);
	_group_buttons->setExclusive(true);

	for (int i = 0; i < 10; ++i) {
		_layout_main->addWidget(_buttons[i] = new QPushButton(QStringLiteral("%1").arg(i+1), this));
		_buttons[i]->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Fixed);
		_buttons[i]->setCheckable(true);
		_buttons[i]->setFocusPolicy(Qt::NoFocus);
		_group_buttons->addButton(_buttons[i], i+1);
	}
}
