#include "BaseEditSearch.h"

#include <QTimer>

Base::EditSearch::EditSearch(QWidget* parent)
	: QLineEdit{parent}
{
	setPlaceholderText(tr("Найти..."));
	setMaxLength(50);
	setFixedWidth(120);

	connect(this, &EditSearch::textChanged, this, &EditSearch::onTextChanged);

	_timer_delay = new QTimer(this);
	_timer_delay->setSingleShot(true);
	_timer_delay->setInterval(500);
	connect(_timer_delay, &QTimer::timeout, this, &EditSearch::onTimerDelay);
}

void Base::EditSearch::onTextChanged(const QString& /*new_text*/)
{
	_timer_delay->start();
}

void Base::EditSearch::onTimerDelay()
{
	auto new_text = text().trimmed();
	if (_search_text != new_text) {
		_search_text = new_text;
		emit findText(_search_text);
	}
}
