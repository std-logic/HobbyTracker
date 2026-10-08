#include "BaseFlowWithComboEdit.h"
#include "BaseFlowItem.h"
#include "BaseComboEdit.h"

Base::FlowWithComboEdit::FlowWithComboEdit(QWidget* parent)
	: FlowContainer{parent}
{
	connect(this, &FlowWithComboEdit::addWidgetRequest,
			this, [this]() { addComboEdit(QString()); });
}

void Base::FlowWithComboEdit::setList(const std::set<QString>& list_of_strings)
{
	_list_of_strings = list_of_strings;
}

void Base::FlowWithComboEdit::setValues(const QStringList& texts)
{
	for (const auto& text : texts) {
		addComboEdit(text);
	}
}

QStringList Base::FlowWithComboEdit::values() const
{
	QStringList texts;
	for (int i = 0; i < count(); ++i) {
		auto edit = comboEditAt(i);
		if (edit && !edit->currentText().isEmpty()) {
			texts.emplace_back(edit->currentText());
		}
	}
	return texts;
}

Base::ComboEdit* Base::FlowWithComboEdit::comboEditAt(int index) const
{
	return dynamic_cast<ComboEdit*>(widgetAt(index));
}

void Base::FlowWithComboEdit::addComboEdit(const QString& text)
{
	auto item = new Base::FlowItem(this);
	auto edit = new Base::ComboEdit(item);
	edit->setTextAndList(text, _list_of_strings);
	item->addWidget(edit);
	addWidget(item);
}
