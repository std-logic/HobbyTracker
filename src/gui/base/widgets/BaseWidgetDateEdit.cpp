#include "BaseWidgetDateEdit.h"

#include <common/Global.h>

#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>

#include <QDate>

Base::WidgetDateEdit::WidgetDateEdit(QWidget* parent)
	: QWidget{parent}
{
	initWidgets();
}

void Base::WidgetDateEdit::setText(const QString& text)
{
	_edit_date->setText(text);
}

QString Base::WidgetDateEdit::text() const
{
	return _edit_date->text();
}

bool Base::WidgetDateEdit::isValid() const
{
	return !_edit_date->text().isEmpty();
}

void Base::WidgetDateEdit::initWidgets()
{
	_layout_main = new QHBoxLayout(this);
	_layout_main->setContentsMargins(0, 0, 0, 0);
	_layout_main->setSpacing(Global::Sizes::default_spacing);

	_edit_date = new QLineEdit(this);
	_edit_date->setPlaceholderText(QStringLiteral("YYYY.MM.DD"));
	_layout_main->addWidget(_edit_date);

	_button_curr = new QPushButton(QIcon::fromTheme(QIcon::ThemeIcon::ViewRefresh), "", this);
	_button_curr->setToolTip(tr("Установить текущую дату"));
	_button_curr->setFixedWidth(24);
	connect(_button_curr, &QPushButton::clicked, this, &WidgetDateEdit::setCurrDate);
	_layout_main->addWidget(_button_curr);

	_button_prev = new QPushButton(QIcon::fromTheme(QIcon::ThemeIcon::GoPrevious), "", this);
	_button_prev->setToolTip(tr("На день раньше"));
	_button_prev->setFixedWidth(24);
	_button_prev->setAutoRepeat(true);
	connect(_button_prev, &QPushButton::clicked, this, &WidgetDateEdit::setPrevDate);
	_layout_main->addWidget(_button_prev);

	_button_next = new QPushButton(QIcon::fromTheme(QIcon::ThemeIcon::GoNext), "", this);
	_button_next->setToolTip(tr("На день позже"));
	_button_next->setFixedWidth(24);
	_button_next->setAutoRepeat(true);
	connect(_button_next, &QPushButton::clicked, this, &WidgetDateEdit::setNextDate);
	_layout_main->addWidget(_button_next);
}

void Base::WidgetDateEdit::setCurrDate()
{
	_edit_date->setText(QDate::currentDate().toString(QStringLiteral("yyyy.MM.dd")));
}

void Base::WidgetDateEdit::setPrevDate()
{
	auto date = QDate::fromString(_edit_date->text(), QStringLiteral("yyyy.MM.dd"));
	if (date.isValid()) {
		_edit_date->setText(date.addDays(-1).toString(QStringLiteral("yyyy.MM.dd")));
	}
}

void Base::WidgetDateEdit::setNextDate()
{
	auto date = QDate::fromString(_edit_date->text(), QStringLiteral("yyyy.MM.dd"));
	if (date.isValid()) {
		_edit_date->setText(date.addDays(1).toString(QStringLiteral("yyyy.MM.dd")));
	}
}
