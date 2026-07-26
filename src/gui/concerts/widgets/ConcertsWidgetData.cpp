#include "ConcertsWidgetData.h"

#include <gui/base/widgets/BaseComboEdit.h>

#include <QLineEdit>

Concerts::WidgetData::WidgetData(size_t index, const DataList& data_list, QWidget* parent)
	: Base::WidgetData{index, data_list.size(), parent}
	, _data_list{data_list}
{
	initData();
	initCommonParams();
	initWidgets();
	copyDataToGui();

	// strictly after initialization finished, because we need only real changes
	connect(_combo_country, &Base::ComboEdit::currentTextChanged,
			this, &Concerts::WidgetData::countryChanged);
	connect(_combo_city, &Base::ComboEdit::currentTextChanged,
			this, &Concerts::WidgetData::cityChanged);
}

void Concerts::WidgetData::initData()
{
	if (_mode_edit_data) { _data = _data_list[_index]; }
}

void Concerts::WidgetData::initCommonParams()
{
	setWindowTitle(_mode_edit_data ?
			tr("Редактирование данных концерта") :
			tr("Добавление нового концерта"));
}

void Concerts::WidgetData::initWidgets()
{
	add(tr("Дата:"), _edit_date);
	_edit_date->setPlaceholderText(tr("YYYY.MM.DD"));

	add(tr("Группы:"), _edit_artists);
	_edit_artists->setPlaceholderText(tr("Список через запятую"));

	add(tr("Описание:"), _combo_description);
	_combo_description->lineEdit()->setPlaceholderText(tr("Необязательное поле"));

	add(tr("Страна:"), _combo_country);

	add(tr("Город:"), _combo_city);

	add(tr("Место:"), _combo_place);
}

void Concerts::WidgetData::copyDataToGui()
{
	if (_mode_edit_data) {
		_edit_date->setText(_data.date());

		_edit_artists->setText(_data.artistsToString());

		_combo_description->setTextAndList(_data.description(), _data_list.listOfDescriptions());

		_combo_country->setTextAndList(_data.country(), _data_list.listOfCountries());

		_combo_city->setTextAndList(_data.city(), _data_list.listOfCities(_data.country()));

		_combo_place->setTextAndList(_data.place(), _data_list.listOfPlaces(_data.city()));
	} else {
		_combo_description->addList(_data_list.listOfDescriptions());

		_combo_country->addList(_data_list.listOfCountries());
	}
}

bool Concerts::WidgetData::copyGuiToData()
{
	if (_edit_date->text().isEmpty()) {
		emit showMessage(tr("Не введена дата!"));
		return false;
	}
	_data.setDate(_edit_date->text());

	_data.setArtistsFromString(_edit_artists->text());

	_data.setDescription(_combo_description->currentText());

	if (_combo_country->currentText().isEmpty()) {
		emit showMessage(tr("Не введена страна!"));
		return false;
	}
	_data.setCountry(_combo_country->currentText());

	if (_combo_city->currentText().isEmpty()) {
		emit showMessage(tr("Не введён город!"));
		return false;
	}
	_data.setCity(_combo_city->currentText());

	if (_combo_place->currentText().isEmpty()) {
		emit showMessage(tr("Не введено место!"));
		return false;
	}
	_data.setPlace(_combo_place->currentText());


	return true;
}

void Concerts::WidgetData::save()
{
	if (copyGuiToData()) {
		emit saveData(_index, _data);
		close();
	}
}

void Concerts::WidgetData::countryChanged(const QString& country)
{
	if (!country.isEmpty() && (_combo_country->findText(country) >= 0)) {
		_combo_city->addList(_data_list.listOfCities(country));
	} else {
		_combo_city->clear();
	}
}

void Concerts::WidgetData::cityChanged(const QString& city)
{
	if (!city.isEmpty() && (_combo_city->findText(city) >= 0)) {
		_combo_place->addList(_data_list.listOfPlaces(city));
	} else {
		_combo_place->clear();
	}
}
