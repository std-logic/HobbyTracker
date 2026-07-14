#include "BikeWidgetData.h"

#include <QLineEdit>
#include <QValidator>

Bike::WidgetData::WidgetData(size_t index, const DataList& data_list, QWidget* parent)
	: Base::WidgetData{index, data_list.size(), parent}
	, _data_list{data_list}
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
	setMinimumWidth(200);
}

void Bike::WidgetData::initWidgets()
{
	add(tr("Год:"), _edit_year);
	_edit_year->setValidator(new QIntValidator(2000, 2100, _edit_year));

	add(tr("Часов:"), _edit_time);
	_edit_time->setValidator(new QIntValidator(0, 10000, _edit_time));

	add(tr("Километров:"), _edit_dist);
	_edit_dist->setValidator(new QIntValidator(0, 100000, _edit_dist));
}

void Bike::WidgetData::copyDataToGui()
{
	if (_mode_edit_data) {
		_edit_year->setText(_data.yearString());

		_edit_time->setText(QString::number(_data.time()));

		_edit_dist->setText(QString::number(_data.dist()));
	} else if (!_data_list.empty()) {
		_edit_year->setText(QString::number(_data_list[_data_list.size()-1].year()+1));
	}
}

bool Bike::WidgetData::copyGuiToData()
{
	if (!_edit_year->hasAcceptableInput()) {
		emit showMessage(tr("Не введён год!"));
		return false;
	}
	_data.setYear(_edit_year->text().toUInt());

	if (!_edit_time->hasAcceptableInput()) {
		emit showMessage(tr("Не введено количество часов!"));
		return false;
	}
	_data.setTime(_edit_time->text().toUInt());

	if (!_edit_dist->hasAcceptableInput()) {
		emit showMessage(tr("Не введено количество километров!"));
		return false;
	}
	_data.setDist(_edit_dist->text().toUInt());

	return true;
}

void Bike::WidgetData::save()
{
	if (copyGuiToData()) {
		emit saveData(_index, _data);
		close();
	}
}
