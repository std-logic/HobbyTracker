#include "GamesWidgetData.h"

#include <gui/base/widgets/BaseComboEdit.h>
#include <gui/base/widgets/BaseWidgetRating.h>

#include <QLineEdit>

Games::WidgetData::WidgetData(size_t index, const DataList& data_list, QWidget* parent)
	: Base::WidgetData{index, data_list.size(), parent}
	, _data_list{data_list}
{
	initData();
	initCommonParams();
	initWidgets();
	copyDataToGui();
}

void Games::WidgetData::initData()
{
	if (_mode_edit_data) { _data = _data_list[_index]; }
}

void Games::WidgetData::initCommonParams()
{
	setWindowTitle(_mode_edit_data ?
			tr("Редактирование данных игры") :
			tr("Добавление новой игры"));
}

void Games::WidgetData::initWidgets()
{
	add(tr("Серия:"), _combo_series);

	add(tr("Название:"), _edit_title);

	add(tr("Разработчик:"), _combo_developer);

	add(tr("Жанр:"), _combo_genre);

	add(tr("Год:"), _edit_year);
	_edit_year->setValidator(new QIntValidator(1900, 2100, _edit_year));

	add(tr("Оценка:"), _widget_rating);
}

void Games::WidgetData::copyDataToGui()
{
	_combo_series->setTextAndList(_data.series(), _data_list.listOfSeries());

	_edit_title->setText(_data.title());

	_combo_developer->setTextAndList(_data.developer(), _data_list.listOfDevelopers());

	_combo_genre->setTextAndList(_data.genre(), _data_list.listOfGenres());

	_edit_year->setText(_data.yearString());

	_widget_rating->setRating(_data.rating());
}

bool Games::WidgetData::copyGuiToData()
{
	if (_combo_series->currentText().isEmpty()) {
		emit showMessage(tr("Не введена серия!"));
		return false;
	}
	_data.setSeries(_combo_series->currentText());

	if (_edit_title->text().isEmpty()) {
		emit showMessage(tr("Не введено название!"));
		return false;
	}
	_data.setTitle(_edit_title->text());

	if (_combo_developer->currentText().isEmpty()) {
		emit showMessage(tr("Не введён разработчик!"));
		return false;
	}
	_data.setDeveloper(_combo_developer->currentText());

	if (_combo_genre->currentText().isEmpty()) {
		emit showMessage(tr("Не введён жанр!"));
		return false;
	}
	_data.setGenre(_combo_genre->currentText());

	if (!_edit_year->hasAcceptableInput()) {
		emit showMessage(tr("Не введён год!"));
		return false;
	}
	_data.setYear(_edit_year->text().toUInt());

	if (!_widget_rating->isValid()) {
		emit showMessage(tr("Не выбрана оценка!"));
		return false;
	}
	_data.setRating(_widget_rating->rating());

	return true;
}

void Games::WidgetData::save()
{
	if (copyGuiToData()) {
		emit saveData(_index, _data);
		close();
	}
}
