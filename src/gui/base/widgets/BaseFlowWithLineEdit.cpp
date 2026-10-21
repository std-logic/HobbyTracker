#include "BaseFlowWithLineEdit.h"
#include "BaseFlowItem.h"

#include <QLineEdit>

Base::FlowWithLineEdit::FlowWithLineEdit(QWidget* parent)
	: FlowContainer{parent}
{
	connect(this, &FlowWithLineEdit::addWidgetRequest,
			this, [this]() { addLineEdit(QString()); });
}

void Base::FlowWithLineEdit::setValues(const QStringList& texts, bool add_one_if_empty)
{
	for (const auto& text : texts) {
		addLineEdit(text);
	}
	if (texts.isEmpty() && add_one_if_empty) {
		addLineEdit(QString());
	}
}

QStringList Base::FlowWithLineEdit::values() const
{
	QStringList texts;
	for (int i = 0; i < count(); ++i) {
		auto edit = lineEditAt(i);
		if (edit && !edit->text().isEmpty()) {
			texts.emplace_back(edit->text());
		}
	}
	return texts;
}

bool Base::FlowWithLineEdit::isValid() const
{
	for (int i = 0; i < count(); ++i) {
		auto edit = lineEditAt(i);
		if (edit && !edit->text().isEmpty()) {
			return true;
		}
	}
	return false;
}

QLineEdit* Base::FlowWithLineEdit::lineEditAt(int index) const
{
	return dynamic_cast<QLineEdit*>(widgetAt(index));
}

void Base::FlowWithLineEdit::addLineEdit(const QString& text)
{
	auto item = new Base::FlowItem(this);
	auto edit = new QLineEdit(item);
	edit->setText(text);
	item->addWidget(edit);
	addWidget(item);
}
