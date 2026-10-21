#include "MoviesWidgetData.h"

#include <gui/base/widgets/BaseComboEdit.h>
#include <gui/base/widgets/BaseFlowWithComboEdit.h>
#include <gui/base/widgets/BaseFlowWithLineEdit.h>
#include <gui/base/widgets/BaseWidgetDateTimeEdit.h>
#include <gui/base/widgets/BaseWidgetRating.h>

#include <QLineEdit>
#include <QCheckBox>
#include <QPushButton>
#include <QHBoxLayout>
#include <QDateTime>

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
	setMinimumWidth(760);
}

void Movies::WidgetData::initWidgets()
{
	add(tr("Название:"), _edit_title_tr);

	add(tr("Название (ориг.):"), _edit_title_orig);
	_edit_title_orig->setPlaceholderText(tr("Необязательное поле"));

	add(tr("Тип:"), _combo_kind);

	add(tr("Жанр:"), _flow_genres);
	_flow_genres->setFixedItemWidth(200);

	addLine();

	add(tr("Страна:"), _flow_countries);
	_flow_countries->setFixedItemWidth(200);

	addLine();

	add(tr("Режиссёр:"), _flow_directors);
	_flow_directors->setFixedItemWidth(200);

	addLine();

	add(tr("Сценарист:"), _flow_writers);
	_flow_writers->setFixedItemWidth(200);

	addLine();

	add(tr("Актёры:"), _flow_actors);
	_flow_actors->setFixedItemWidth(200);

	add(tr("Длительность:"), _edit_time);

	add(tr("Год:"), _edit_year);

	add(tr("Оценка:"), _widget_rating);

	add(tr("Дата:"), _edit_view_date);

	add(tr("Избранное:"), _check_favorite);
}

void Movies::WidgetData::copyDataToGui()
{
	if (_mode_edit_data) {
		_edit_title_tr->setText(_data.titleTr());

		_edit_title_orig->setText(_data.titleOrig());

		_combo_kind->setTextAndList(_data.kind(), _data_list.listOfKinds());

		_edit_time->setText(QString::number(_data.time()));

		_edit_year->setText(_data.yearString());

		_widget_rating->setRating(_data.rating());

		_edit_view_date->setText(_data.viewDate());

		_check_favorite->setChecked(_data.isFavorite());
	} else {
		_combo_kind->setList(_data_list.listOfKinds());
	}

	_flow_genres->setList(_data_list.listOfGenres());
	_flow_genres->setValues(_data.genres(), true);

	_flow_countries->setList(_data_list.listOfCountries());
	_flow_countries->setValues(_data.countries(), true);

	_flow_directors->setList(_data_list.listOfDirectors());
	_flow_directors->setValues(_data.directors(), true);

	_flow_writers->setList(_data_list.listOfWriters());
	_flow_writers->setValues(_data.writers(), true);

	_flow_actors->setValues(_data.actors(), true);
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

	if (!_flow_genres->isValid()) {
		emit showMessage(tr("Не введён жанр!"));
		return false;
	}
	_data.setGenres(_flow_genres->values());

	if (!_flow_countries->isValid()) {
		emit showMessage(tr("Не введена страна!"));
		return false;
	}
	_data.setCountries(_flow_countries->values());

	_data.setDirectors(_flow_directors->values());

	_data.setWriters(_flow_writers->values());

	_data.setActors(_flow_actors->values());

	if (_edit_time->text().isEmpty()) {
		emit showMessage(tr("Не введена длительность!"));
		return false;
	}
	_data.setTime(_edit_time->text().toUInt());

	if (_edit_year->text().isEmpty()) {
		emit showMessage(tr("Не введён год!"));
		return false;
	}
	_data.setYearFromString(_edit_year->text());

	if (!_widget_rating->isValid()) {
		emit showMessage(tr("Не выбрана оценка!"));
		return false;
	}
	_data.setRating(_widget_rating->rating());

	if (!_edit_view_date->isValid()) {
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
