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
	addWidget(tr("Серия:"), _combo_series = new Base::ComboEdit(this));

	addWidget(tr("Название:"), _edit_title = new QLineEdit(this));

	addWidget(tr("Разработчик:"), _combo_developer = new Base::ComboEdit(this));

	addWidget(tr("Жанр:"), _combo_genre = new Base::ComboEdit(this));

	addWidget(tr("Год:"), _edit_year = new QLineEdit(this));
	_edit_year->setValidator(new QIntValidator(1900, 2100, _edit_year));

	addWidget(tr("Оценка:"), _widget_rating = new Base::WidgetRating(this));
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
	_data.setSeries(_combo_series->currentText());
	if (_data.series().isEmpty()) {
		emit showMessage(tr("Не введена серия!"));
		return false;
	}

	_data.setTitle(_edit_title->text());
	if (_data.title().isEmpty()) {
		emit showMessage(tr("Не введено название!"));
		return false;
	}

	_data.setDeveloper(_combo_developer->currentText());
	if (_data.developer().isEmpty()) {
		emit showMessage(tr("Не введён разработчик!"));
		return false;
	}

	_data.setGenre(_combo_genre->currentText());
	if (_data.genre().isEmpty()) {
		emit showMessage(tr("Не введён жанр!"));
		return false;
	}

	_data.setYear(_edit_year->text().toUInt());
	if ((_data.year() < 1900) || (2100 < _data.year())) {
		emit showMessage(tr("Не введён год!"));
		return false;
	}

	_data.setRating(_widget_rating->rating());
	if ((_data.rating() < 1) || (10 < _data.rating())) {
		emit showMessage(tr("Не выбрана оценка!"));
		return false;
	}

	return true;
}

void Games::WidgetData::save()
{
	if (copyGuiToData()) {
		emit saveData(_index, _data);
		close();
	}
}
