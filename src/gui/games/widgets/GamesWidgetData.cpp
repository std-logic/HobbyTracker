#include "GamesWidgetData.h"

#include <gui/base/widgets/BaseComboEdit.h>
#include <gui/base/widgets/BaseWidgetRating.h>

#include <QLineEdit>

Games::WidgetData::WidgetData(size_t index, const DataList& list, QWidget* parent)
	: Base::WidgetData{parent}
	, _index{index}
	, _data_list{list}
{
	initData();
	initCommonParams();
	initWidgets();
	copyDataToGui();
}

void Games::WidgetData::initData()
{
	if (_index < _data_list.size()) { _data = _data_list[_index]; }
}

void Games::WidgetData::initCommonParams()
{
	setWindowTitle((_index < _data_list.size()) ?
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
	_combo_series->addList(_data_list.listOfSeries());
	_combo_series->lineEdit()->setText(_data.series());

	_edit_title->setText(_data.title());

	_combo_developer->addList(_data_list.listOfDevelopers());
	_combo_developer->lineEdit()->setText(_data.developer());

	_combo_genre->addList(_data_list.listOfGenres());
	_combo_genre->lineEdit()->setText(_data.genre());

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
