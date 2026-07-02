#include "BaseComboEdit.h"

Base::ComboEdit::ComboEdit(QWidget* parent)
	: QComboBox{parent}
{
	setEditable(true);
	setInsertPolicy(QComboBox::NoInsert);
}

void Base::ComboEdit::addList(const std::set<QString>& list_of_strings)
{
	clear();
	for (const auto& str : list_of_strings) {
		if (!str.isEmpty()) {
			addItem(str);
		}
	}
	setCurrentIndex(-1);
}
