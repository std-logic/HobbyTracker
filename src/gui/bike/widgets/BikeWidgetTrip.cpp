#include "BikeWidgetTrip.h"

#include <gui/base/widgets/BaseFlowWithComboEdit.h>
#include <gui/base/widgets/BaseWidgetDateEdit.h>
#include <gui/base/widgets/BaseWidgetFileEdit.h>

#include <QLineEdit>
#include <QValidator>

Bike::WidgetTrip::WidgetTrip(size_t index, const TripList& list,
							 const QString& photo_dir, QWidget* parent)
	: Base::WidgetData{index, list.size(), parent}
	, _data_list{list}
{
	initData();
	initCommonParams();
	initWidgets(photo_dir);
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
	setMinimumWidth(700);
}

void Bike::WidgetTrip::initWidgets(const QString& photo_dir)
{
	add(tr("Старт:"), _edit_date_start);

	add(tr("Финиш:"), _edit_date_end);

	add(tr("Ночёвок:"), _edit_time);
	_edit_time->setValidator(new QIntValidator(0, 10000, _edit_time));

	add(tr("Километров:"), _edit_dist);
	_edit_dist->setValidator(new QIntValidator(0, 100000, _edit_dist));

	add(tr("Страны:"), _flow_countries);
	_flow_countries->setFixedItemWidth(190);

	addLine();

	add(tr("Маршрут:"), _flow_places);
	_flow_places->setFixedItemWidth(190);

	add(tr("Фото:"), _widget_photos);
	_widget_photos->setMode(Base::WidgetFileEdit::ChooseMode::File);
	_widget_photos->setStartDir(photo_dir);
}

void Bike::WidgetTrip::copyDataToGui()
{
	if (_mode_edit_data) {
		_edit_date_start->setText(_data.dateStart());

		_edit_date_end->setText(_data.dateEnd());

		_edit_time->setText(QString::number(_data.time()));

		_edit_dist->setText(QString::number(_data.dist()));

		_widget_photos->setText(_data.photoLink());
	}

	_flow_countries->setList(_data_list.listOfCountries());
	_flow_countries->setValues(_data.countries(), true);

	_flow_places->setList(_data_list.listOfPlaces());
	_flow_places->setValues(_data.places(), true);
}

bool Bike::WidgetTrip::copyGuiToData()
{
	if (!_edit_date_start->isValid()) {
		emit showMessage(tr("Не введена дата старта!"));
		return false;
	}
	_data.setDateStart(_edit_date_start->text());

	if (!_edit_date_end->isValid()) {
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

	if (!_flow_countries->isValid()) {
		emit showMessage(tr("Не введены страны!"));
		return false;
	}
	_data.setCountries(_flow_countries->values());

	if (!_flow_places->isValid()) {
		emit showMessage(tr("Не введён маршрут!"));
		return false;
	}
	_data.setPlaces(_flow_places->values());

	_data.setPhotoLink(_widget_photos->text());

	return true;
}

void Bike::WidgetTrip::save()
{
	if (copyGuiToData()) {
		emit saveData(_index, _data);
		close();
	}
}
