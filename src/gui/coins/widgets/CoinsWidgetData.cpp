#include "CoinsWidgetData.h"

#include <gui/base/widgets/BaseComboEdit.h>

#include <QLineEdit>

Coins::WidgetData::WidgetData(size_t index, const DataList& data_list, QWidget* parent)
	: Base::WidgetData{index, data_list.size(), parent}
	, _data_list{data_list}
{
	initData();
	initCommonParams();
	initWidgets();
	copyDataToGui();

	// strictly after initialization finished, because we need only real changes
	connect(_combo_country, &Base::ComboEdit::currentTextChanged,
			this, &Coins::WidgetData::countryChanged);
	connect(_combo_period, &Base::ComboEdit::currentTextChanged,
			this, &Coins::WidgetData::periodChanged);
}

void Coins::WidgetData::initData()
{
	if (_mode_edit_data) { _data = _data_list[_index]; }
}

void Coins::WidgetData::initCommonParams()
{
	setWindowTitle(_mode_edit_data ?
			tr("Редактирование данных монеты") :
			tr("Добавление новой монеты"));
}

void Coins::WidgetData::initWidgets()
{
	add(tr("Страна:"), _combo_country);

	add(tr("Период:"), _combo_period);

	add(tr("Валюта:"), _combo_currency);

	add(tr("Номинал:"), _combo_value);

	add(tr("Название:"), _edit_title);
	_edit_title->setPlaceholderText(tr("Необязательное поле"));

	add(tr("Диаметр, мм:"), _edit_diameter);

	add(tr("Номер:"), _edit_number);

	add(tr("Год:"), _edit_year);
	_edit_year->setValidator(new QIntValidator(1, 2100, _edit_year));

	add(tr("Разновидность:"), _edit_version);
	_edit_version->setPlaceholderText(tr("Необязательное поле"));

	add(tr("Состояние:"), _combo_state);
	_combo_state->lineEdit()->setPlaceholderText(tr("Необязательное поле"));
}

void Coins::WidgetData::copyDataToGui()
{
	if (_mode_edit_data) {
		_combo_country->setTextAndList(_data.country(),
				_data_list.listOfCountries());

		_combo_period->setTextAndList(_data.period(),
				_data_list.listOfPeriods(_data.country()));

		_combo_currency->setTextAndList(_data.currency(),
				_data_list.listOfCurrencies(_data.country(), _data.period()));

		_combo_value->setTextAndList(_data.value(),
				_data_list.listOfValues(_data.country(), _data.period()));

		_edit_title->setText(_data.title());

		_edit_diameter->setText(_data.diameter());

		_edit_number->setText(_data.number());

		_edit_year->setText(_data.yearString());

		_edit_version->setText(_data.version());

		_combo_state->setTextAndList(_data.state(), _data_list.listOfStates());
	} else {
		_combo_country->addList(_data_list.listOfCountries());

		_combo_state->addList(_data_list.listOfStates());
	}
}

bool Coins::WidgetData::copyGuiToData()
{
	if (_combo_country->currentText().isEmpty()) {
		emit showMessage(tr("Не введена страна!"));
		return false;
	}
	_data.setCountry(_combo_country->currentText());

	if (_combo_period->currentText().isEmpty()) {
		emit showMessage(tr("Не введён период!"));
		return false;
	}
	_data.setPeriod(_combo_period->currentText());

	if (_combo_currency->currentText().isEmpty()) {
		emit showMessage(tr("Не введена валюта!"));
		return false;
	}
	_data.setCurrency(_combo_currency->currentText());

	if (_combo_value->currentText().isEmpty()) {
		emit showMessage(tr("Не введён номинал!"));
		return false;
	}
	_data.setValue(_combo_value->currentText());

	_data.setTitle(_edit_title->text());

	if (_edit_diameter->text().isEmpty()) {
		emit showMessage(tr("Не введён диаметр!"));
		return false;
	}
	_data.setDiameter(_edit_diameter->text());

	if (_edit_number->text().isEmpty()) {
		emit showMessage(tr("Не введён номер!"));
		return false;
	}
	_data.setNumber(_edit_number->text());

	if (!_edit_year->hasAcceptableInput()) {
		emit showMessage(tr("Не введён год!"));
		return false;
	}
	_data.setYear(_edit_year->text().toUInt());

	_data.setVersion(_edit_version->text());

	_data.setState(_combo_state->currentText());

	return true;
}

void Coins::WidgetData::save()
{
	if (copyGuiToData()) {
		emit saveData(_index, _data);
		close();
	}
}

void Coins::WidgetData::countryChanged(const QString& country)
{
	if (!country.isEmpty() && (_combo_country->findText(country) >= 0)) {
		_combo_period->addList(_data_list.listOfPeriods(country), true);
	} else {
		_combo_period->clear();
	}
}

void Coins::WidgetData::periodChanged(const QString& period)
{
	if (!period.isEmpty() && (_combo_period->findText(period) >= 0)) {
		_combo_currency->addList(_data_list.listOfCurrencies(_combo_country->currentText(), period), true);
		_combo_value->addList(_data_list.listOfValues(_combo_country->currentText(), period));
	} else {
		_combo_currency->clear();
		_combo_value->clear();
	}
}
