#include "BaseWidgetExtra.h"
#include "BaseComboEdit.h"

#include <QLineEdit>

Base::WidgetExtra::WidgetExtra(size_t index, const ExtraList& list, QWidget* parent)
	: Base::WidgetData{index, list.size(), parent}
	, _data_list{list}
{
	initData();
	initCommonParams();
	initWidgets();
	copyDataToGui();
}

void Base::WidgetExtra::initData()
{
	if (_mode_edit_data) { _data = _data_list[_index]; }
}

void Base::WidgetExtra::initCommonParams()
{
	setWindowTitle(_mode_edit_data ?
			tr("Редактирование записи") :
			tr("Добавление новой записи"));
}

void Base::WidgetExtra::initWidgets()
{
	addWidget(tr("Список:"), _combo_group = new Base::ComboEdit(this));

	addWidget(tr("Запись:"), _edit_title = new QLineEdit(this));

	addWidget(tr("Комментарий:"), _edit_notes = new QLineEdit(this));
	_edit_notes->setPlaceholderText(tr("Необязательное поле"));
}

void Base::WidgetExtra::copyDataToGui()
{
	_combo_group->setTextAndList(_data.group(), _data_list.listOfGroups());

	_edit_title->setText(_data.title());

	_edit_notes->setText(_data.notes());
}

bool Base::WidgetExtra::copyGuiToData()
{
	_data.setGroup(_combo_group->currentText());
	if (_data.group().isEmpty()) {
		emit showMessage(tr("Не введено название списка!"));
		return false;
	}

	_data.setTitle(_edit_title->text());
	if (_data.title().isEmpty()) {
		emit showMessage(tr("Не введена запись!"));
		return false;
	}

	_data.setNotes(_edit_notes->text());

	return true;
}

void Base::WidgetExtra::save()
{
	if (copyGuiToData()) {
		emit saveExtra(_index, _data);
		close();
	}
}
