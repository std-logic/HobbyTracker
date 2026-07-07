#include "BikeWidgetData.h"

#include <QLineEdit>
#include <QValidator>

Bike::WidgetData::WidgetData(size_t index, const DataList& list, QWidget* parent)
	: Base::WidgetData{parent}
	, _index{index}
	, _data_list{list}
{
	initData();
	initCommonParams();
	initWidgets();
	copyDataToGui();
}

void Bike::WidgetData::initData()
{
	if (_index < _data_list.size()) { _data = _data_list[_index]; }
}

void Bike::WidgetData::initCommonParams()
{
	setWindowTitle((_index < _data_list.size()) ?
					tr("Редактирование данных") :
					tr("Добавление новых данных"));
}

void Bike::WidgetData::initWidgets()
{
	addWidget(tr("Год:"), _edit_year = new QLineEdit(this));
	_edit_year->setValidator(new QIntValidator(2000, 2100, _edit_year));

	addWidget(tr("Пробег, км:"), _edit_dist = new QLineEdit(this));
	_edit_dist->setValidator(new QIntValidator(0, 10000, _edit_dist));

	addWidget(tr("Время, ч:"), _edit_time = new QLineEdit(this));
	_edit_time->setValidator(new QIntValidator(0, 1000, _edit_time));
}

void Bike::WidgetData::copyDataToGui()
{
	if (_data.year() != Global::undefined_value) {
		_edit_year->setText(_data.yearString());
	} else if (!_data_list.empty()) {
		_edit_year->setText(QString::number(_data_list[_data_list.size()-1].year()+1));
	}

	_edit_dist->setText(QString::number(_data.dist()));

	_edit_time->setText(QString::number(_data.time()));
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
