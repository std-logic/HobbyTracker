#include "BaseComboEdit.h"

#include <QLineEdit>

Base::ComboEdit::ComboEdit(QWidget* parent)
	: QComboBox{parent}
{
	setEditable(true);
	setInsertPolicy(QComboBox::NoInsert);
}

void Base::ComboEdit::addList(const std::set<QString>& list_of_strings, bool choose_if_single)
{
	clear();
	for (const auto& str : list_of_strings) {
		if (!str.isEmpty()) {
			addItem(str);
		}
	}
	if ((count() == 1) && choose_if_single) { return; }
	setCurrentIndex(-1);
}

void Base::ComboEdit::setTextAndList(const QString& text, const std::set<QString>& list_of_strings)
{
	addList(list_of_strings);
	lineEdit()->setText(text);
}
