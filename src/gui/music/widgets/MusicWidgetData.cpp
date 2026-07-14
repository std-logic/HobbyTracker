#include "MusicWidgetData.h"

#include <gui/base/widgets/BaseComboEdit.h>

#include <QLineEdit>
#include <QCheckBox>

Music::WidgetData::WidgetData(size_t index, const DataList& data_list, QWidget* parent)
	: Base::WidgetData{index, data_list.size(), parent}
	, _data_list{data_list}
{
	initData();
	initCommonParams();
	initWidgets();
	copyDataToGui();
}

void Music::WidgetData::initData()
{
	if (_mode_edit_data) { _data = _data_list[_index]; }
}

void Music::WidgetData::initCommonParams()
{
	setWindowTitle(_mode_edit_data ?
			tr("Редактирование данных группы") :
			tr("Добавление новой группы"));
}

void Music::WidgetData::initWidgets()
{
	add(tr("Название:"), _edit_title);

	add(tr("Жанр:"), _combo_genre);

	add(tr("Страна основания:"), _combo_country);

	add(tr("Год основания:"), _edit_year);
	_edit_year->setValidator(new QIntValidator(1, 2100, _edit_year));

	add(tr("Статус:"), _check_state);
	_check_state->setText(tr("Активна"));
}

void Music::WidgetData::copyDataToGui()
{
	_edit_title->setText(_data.title());

	_combo_genre->setTextAndList(_data.genre(), _data_list.listOfGenres());

	_combo_country->setTextAndList(_data.country(), _data_list.listOfCountries());

	_edit_year->setText(_data.yearString());

	_check_state->setChecked(_data.isActive());
}

bool Music::WidgetData::copyGuiToData()
{
	if (_edit_title->text().isEmpty()) {
		emit showMessage(tr("Не введено название!"));
		return false;
	}
	_data.setTitle(_edit_title->text());

	if (_combo_genre->currentText().isEmpty()) {
		emit showMessage(tr("Не введён жанр!"));
		return false;
	}
	_data.setGenre(_combo_genre->currentText());

	if (_combo_country->currentText().isEmpty()) {
		emit showMessage(tr("Не введена страна основания!"));
		return false;
	}
	_data.setCountry(_combo_country->currentText());

	if (!_edit_year->hasAcceptableInput()) {
		emit showMessage(tr("Не введён год основания!"));
		return false;
	}
	_data.setYear(_edit_year->text().toUInt());

	_data.setState(_check_state->isChecked() ? States::Active : States::Inactive);

	return true;
}

void Music::WidgetData::save()
{
	if (copyGuiToData()) {
		emit saveData(_index, _data);
		close();
	}
}
