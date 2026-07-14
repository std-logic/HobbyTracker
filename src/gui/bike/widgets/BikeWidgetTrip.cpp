#include "BikeWidgetTrip.h"

#include <QLineEdit>
#include <QValidator>

Bike::WidgetTrip::WidgetTrip(size_t index, const TripList& list, QWidget* parent)
	: Base::WidgetData{index, list.size(), parent}
	, _data_list{list}
{
	initData();
	initCommonParams();
	initWidgets();
	copyDataToGui();
}

void Bike::WidgetTrip::initData()
{
	if (_mode_edit_data) { _data = _data_list[_index]; }
}

void Bike::WidgetTrip::initCommonParams()
{
	setWindowTitle(_mode_edit_data ?
			tr("Редактирование велопохода") :
			tr("Добавление нового велопохода"));
}

void Bike::WidgetTrip::initWidgets()
{
	add(tr("Старт:"), _edit_date_start);
	_edit_date_start->setPlaceholderText(tr("YYYY.MM.DD"));

	add(tr("Финиш:"), _edit_date_end);
	_edit_date_end->setPlaceholderText(tr("YYYY.MM.DD"));

	add(tr("Ночёвок:"), _edit_time);
	_edit_time->setValidator(new QIntValidator(0, 10000, _edit_time));

	add(tr("Километров:"), _edit_dist);
	_edit_dist->setValidator(new QIntValidator(0, 100000, _edit_dist));

	add(tr("Страны:"), _edit_countries);
	_edit_countries->setPlaceholderText(tr("Список через запятую"));

	add(tr("Места:"), _edit_places);
	_edit_places->setPlaceholderText(tr("Список через запятую"));
}

void Bike::WidgetTrip::copyDataToGui()
{
	if (_mode_edit_data) {
		_edit_date_start->setText(_data.dateStart());

		_edit_date_end->setText(_data.dateEnd());

		_edit_time->setText(QString::number(_data.time()));

		_edit_dist->setText(QString::number(_data.dist()));

		_edit_countries->setText(_data.countriesToString());

		_edit_places->setText(_data.placesToString());
	}
}

bool Bike::WidgetTrip::copyGuiToData()
{
	if (_edit_date_start->text().isEmpty()) {
		emit showMessage(tr("Не введена дата старта!"));
		return false;
	}
	_data.setDateStart(_edit_date_start->text());

	if (_edit_date_end->text().isEmpty()) {
		emit showMessage(tr("Не введена дата финиша!"));
		return false;
	}
	_data.setDateEnd(_edit_date_end->text());

	if (!_edit_time->hasAcceptableInput()) {
		emit showMessage(tr("Не введено количество ночёвок!"));
		return false;
	}
	_data.setTime(_edit_time->text().toUInt());

	if (!_edit_dist->hasAcceptableInput()) {
		emit showMessage(tr("Не введено количество километров!"));
		return false;
	}
	_data.setDist(_edit_dist->text().toUInt());

	if (_edit_countries->text().isEmpty()) {
		emit showMessage(tr("Не введены страны!"));
		return false;
	}
	_data.setCountriesFromString(_edit_countries->text());

	if (_edit_places->text().isEmpty()) {
		emit showMessage(tr("Не введены места!"));
		return false;
	}
	_data.setPlacesFromString(_edit_places->text());

	return true;
}

void Bike::WidgetTrip::save()
{
	if (copyGuiToData()) {
		emit saveData(_index, _data);
		close();
	}
}
