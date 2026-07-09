#include "BikeWidgetData.h"

#include <QLineEdit>
#include <QValidator>

Bike::WidgetData::WidgetData(size_t index, const DataList& list, QWidget* parent)
	: Base::WidgetData{index, list.size(), parent}
	, _data_list{list}
{
	initData();
	initCommonParams();
	initWidgets();
	copyDataToGui();
}

void Bike::WidgetData::initData()
{
	if (_mode_edit_data) { _data = _data_list[_index]; }
}

void Bike::WidgetData::initCommonParams()
{
	setWindowTitle(_mode_edit_data ?
			tr("Редактирование данных") :
			tr("Добавление новых данных"));
}

void Bike::WidgetData::initWidgets()
{
	addWidget(tr("Год:"), _edit_year = new QLineEdit(this));
	_edit_year->setValidator(new QIntValidator(2000, 2100, _edit_year));

	addWidget(tr("Километров:"), _edit_dist = new QLineEdit(this));
	_edit_dist->setValidator(new QIntValidator(0, 10000, _edit_dist));

	addWidget(tr("Часов:"), _edit_time = new QLineEdit(this));
	_edit_time->setValidator(new QIntValidator(0, 1000, _edit_time));
}

void Bike::WidgetData::copyDataToGui()
{
	if (_mode_edit_data) {
		_edit_year->setText(_data.yearString());
	} else if (!_data_list.empty()) {
		_edit_year->setText(QString::number(_data_list[_data_list.size()-1].year()+1));
	}

	if (_mode_edit_data) {
		_edit_dist->setText(QString::number(_data.dist()));

		_edit_time->setText(QString::number(_data.time()));
	}
}

bool Bike::WidgetData::copyGuiToData()
{
	_data.setYear(_edit_year->text().toUInt());
	if ((_data.year() < 2000) || (2100 < _data.year())) {
		emit showMessage(tr("Не введён год!"));
		return false;
	}

	if (_edit_dist->text().isEmpty()) {
		emit showMessage(tr("Не введён пробег!"));
		return false;
	}
	_data.setDist(_edit_dist->text().toUInt());

	if (_edit_time->text().isEmpty()) {
		emit showMessage(tr("Не введено время!"));
		return false;
	}
	_data.setTime(_edit_time->text().toUInt());

	return true;
}

void Bike::WidgetData::save()
{
	if (copyGuiToData()) {
		emit saveData(_index, _data);
		close();
	}
}
