#include "BaseWidgetDateTimeEdit.h"

#include <common/Global.h>

#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>

#include <QDateTime>

Base::WidgetDateTimeEdit::WidgetDateTimeEdit(QWidget* parent)
	: QWidget{parent}
{
	initWidgets();
}

void Base::WidgetDateTimeEdit::setText(const QString& text)
{
	_edit_date->setText(text);
}

QString Base::WidgetDateTimeEdit::text() const
{
	return _edit_date->text();
}

bool Base::WidgetDateTimeEdit::isValid() const
{
	return !_edit_date->text().isEmpty();
}

void Base::WidgetDateTimeEdit::initWidgets()
{
	_layout_main = new QHBoxLayout(this);
	_layout_main->setContentsMargins(0, 0, 0, 0);
	_layout_main->setSpacing(Global::Sizes::default_spacing);

	_edit_date = new QLineEdit(this);
	_edit_date->setPlaceholderText(QStringLiteral("YYYY.MM.DD HH:MM:SS"));
	_layout_main->addWidget(_edit_date);

	_button_curr = new QPushButton(QIcon::fromTheme(QIcon::ThemeIcon::ViewRefresh), "", this);
	_button_curr->setToolTip(tr("Установить текущее время"));
	_button_curr->setFixedWidth(24);
	connect(_button_curr, &QPushButton::clicked, this, &WidgetDateTimeEdit::setCurrDate);
	_layout_main->addWidget(_button_curr);
}

void Base::WidgetDateTimeEdit::setCurrDate()
{
	_edit_date->setText(QDateTime::currentDateTime().toString(QStringLiteral("yyyy.MM.dd HH:mm:ss")));
}
