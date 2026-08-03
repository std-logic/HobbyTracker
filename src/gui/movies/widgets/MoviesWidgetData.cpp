#include "MoviesWidgetData.h"

#include <gui/base/widgets/BaseComboEdit.h>
#include <gui/base/widgets/BaseWidgetRating.h>

#include <QLineEdit>
#include <QCheckBox>

Movies::WidgetData::WidgetData(size_t index, const DataList& data_list, QWidget* parent)
	: Base::WidgetData{index, data_list.size(), parent}
	, _data_list{data_list}
{
	initData();
	initCommonParams();
	initWidgets();
	copyDataToGui();
}

void Movies::WidgetData::initData()
{
	if (_mode_edit_data) { _data = _data_list[_index]; }
}

void Movies::WidgetData::initCommonParams()
{
	setWindowTitle(_mode_edit_data ?
			tr("Редактирование данных произведения") :
			tr("Добавление нового произведения"));
	setMinimumWidth(800);
}

void Movies::WidgetData::initWidgets()
{
	add(tr("Название:"), _edit_title_tr);

	add(tr("Название (ориг.):"), _edit_title_orig);
	_edit_title_orig->setPlaceholderText(tr("Необязательное поле"));

	add(tr("Тип:"), _combo_kind);

	add(tr("Жанр:"), _edit_genres);
	_edit_genres->setPlaceholderText(tr("Список через запятую"));

	add(tr("Страна:"), _edit_countries);
	_edit_countries->setPlaceholderText(tr("Список через запятую"));

	add(tr("Режиссёр:"), _edit_directors);
	_edit_directors->setPlaceholderText(tr("Список через запятую"));

	add(tr("Сценарист:"), _edit_writers);
	_edit_writers->setPlaceholderText(tr("Список через запятую"));

	add(tr("Актёры:"), _edit_actors);
	_edit_actors->setPlaceholderText(tr("Список через запятую"));

	add(tr("Длительность:"), _edit_time);

	add(tr("Год:"), _edit_year);

	add(tr("Оценка:"), _widget_rating);

	add(tr("Дата:"), _edit_view_date);
	_edit_view_date->setPlaceholderText(tr("YYYY.MM.DD HH:MM:SS"));

	add(tr("Избранное:"), _check_favorite);
}

void Movies::WidgetData::copyDataToGui()
{
	if (_mode_edit_data) {
		_edit_title_tr->setText(_data.titleTr());

		_edit_title_orig->setText(_data.titleOrig());

		_combo_kind->setTextAndList(_data.kind(), _data_list.listOfKinds());

		_edit_genres->setText(_data.genresToString());

		_edit_countries->setText(_data.countriesToString());

		_edit_directors->setText(_data.directorsToString());

		_edit_writers->setText(_data.writersToString());

		_edit_actors->setText(_data.actorsToString());

		_edit_time->setText(QString::number(_data.time()));

		_edit_year->setText(_data.yearString());

		_widget_rating->setRating(_data.rating());

		_edit_view_date->setText(_data.viewDate());

		_check_favorite->setChecked(_data.isFavorite());
	} else {
		_combo_kind->addList(_data_list.listOfKinds());
	}
}

bool Movies::WidgetData::copyGuiToData()
{
	if (_edit_title_tr->text().isEmpty()) {
		emit showMessage(tr("Не введено название!"));
		return false;
	}
	_data.setTitleTr(_edit_title_tr->text());

	_data.setTitleOrig(_edit_title_orig->text());

	if (_combo_kind->currentText().isEmpty()) {
		emit showMessage(tr("Не введён тип!"));
		return false;
	}
	_data.setKind(_combo_kind->currentText());

	if (_edit_genres->text().isEmpty()) {
		emit showMessage(tr("Не введён жанр!"));
		return false;
	}
	_data.setGenresFromString(_edit_genres->text());

	if (_edit_countries->text().isEmpty()) {
		emit showMessage(tr("Не введена страна!"));
		return false;
	}
	_data.setCountriesFromString(_edit_countries->text());

	if (_edit_directors->text().isEmpty()) {
		emit showMessage(tr("Не введён режиссёр!"));
		return false;
	}
	_data.setDirectorsFromString(_edit_directors->text());

	if (_edit_writers->text().isEmpty()) {
		emit showMessage(tr("Не введён сценарист!"));
		return false;
	}
	_data.setWritersFromString(_edit_writers->text());

	if (_edit_actors->text().isEmpty()) {
		emit showMessage(tr("Не введены актёры!"));
		return false;
	}
	_data.setActorsFromString(_edit_actors->text());

	if (_edit_time->text().isEmpty()) {
		emit showMessage(tr("Не введена длительность!"));
		return false;
	}
	_data.setTime(_edit_time->text().toUInt());

	if (!_edit_year->text().isEmpty()) {
		emit showMessage(tr("Не введён год!"));
		return false;
	}
	_data.setYearFromString(_edit_year->text());

	if (!_widget_rating->isValid()) {
		emit showMessage(tr("Не выбрана оценка!"));
		return false;
	}
	_data.setRating(_widget_rating->rating());

	if (_edit_view_date->text().isEmpty()) {
		emit showMessage(tr("Не введена дата!"));
		return false;
	}
	_data.setViewDate(_edit_view_date->text());

	_data.setFavorite(_check_favorite->isChecked());

	return true;
}

void Movies::WidgetData::save()
{
	if (copyGuiToData()) {
		emit saveData(_index, _data);
		close();
	}
}
