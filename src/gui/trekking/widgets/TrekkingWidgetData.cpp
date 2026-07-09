#include "TrekkingWidgetData.h"

#include <gui/base/widgets/BaseComboEdit.h>

#include <QLineEdit>
#include <QValidator>

Trekking::WidgetData::WidgetData(size_t index, const DataList& data_list, QWidget* parent)
	: Base::WidgetData{index, data_list.size(), parent}
	, _data_list{data_list}
{
	initData();
	initCommonParams();
	initWidgets();
	copyDataToGui();
}

void Trekking::WidgetData::initData()
{
	if (_mode_edit_data) { _data = _data_list[_index]; }
}

void Trekking::WidgetData::initCommonParams()
{
	setWindowTitle(_mode_edit_data ?
			tr("Редактирование похода") :
			tr("Добавление нового похода"));
}

void Trekking::WidgetData::initWidgets()
{
	addWidget(tr("Старт:"), _edit_date_start = new QLineEdit(this));
	_edit_date_start->setPlaceholderText(tr("YYYY.MM.DD"));

	addWidget(tr("Финиш:"), _edit_date_end = new QLineEdit(this));
	_edit_date_end->setPlaceholderText(tr("YYYY.MM.DD"));

	addWidget(tr("Ночёвок:"), _edit_time = new QLineEdit(this));
	_edit_time->setValidator(new QIntValidator(0, 1000, _edit_time));

	addWidget(tr("Километров:"), _edit_dist = new QLineEdit(this));
	_edit_dist->setValidator(new QIntValidator(0, 10000, _edit_dist));

	addWidget(tr("Высшая точка:"), _edit_peak = new QLineEdit(this));
	_edit_peak->setValidator(new QIntValidator(0, 10000, _edit_peak));

	addWidget(tr("Тип:"), _combo_kind = new Base::ComboEdit(this));

	addWidget(tr("Страны:"), _edit_countries = new QLineEdit(this));
	_edit_countries->setPlaceholderText(tr("Список через запятую"));

	addWidget(tr("Место:"), _edit_places = new QLineEdit(this));
}

void Trekking::WidgetData::copyDataToGui()
{
	if (_mode_edit_data) {
		_edit_date_start->setText(_data.dateStart());

		_edit_date_end->setText(_data.dateEnd());

		_edit_time->setText(QString::number(_data.time()));

		_edit_dist->setText(QString::number(_data.dist()));

		_edit_peak->setText(QString::number(_data.peak()));

		_edit_countries->setText(_data.countriesToString());

		_edit_places->setText(_data.places());
	}

	_combo_kind->setTextAndList(_data.kind(), _data_list.listOfKinds());
}

bool Trekking::WidgetData::copyGuiToData()
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

	if (_edit_time->text().isEmpty()) {
		emit showMessage(tr("Не введено количество ночёвок!"));
		return false;
	}
	_data.setTime(_edit_time->text().toUInt());

	if (_edit_dist->text().isEmpty()) {
		emit showMessage(tr("Не введено количество километров!"));
		return false;
	}
	_data.setDist(_edit_dist->text().toUInt());

	if (_edit_peak->text().isEmpty()) {
		emit showMessage(tr("Не введена высшая точка!"));
		return false;
	}
	_data.setPeak(_edit_peak->text().toUInt());

	if (_combo_kind->currentText().isEmpty()) {
		emit showMessage(tr("Не введён тип!"));
		return false;
	}
	_data.setKind(_combo_kind->currentText());

	if (_edit_countries->text().isEmpty()) {
		emit showMessage(tr("Не введены страны!"));
		return false;
	}
	_data.setCountriesFromString(_edit_countries->text());

	if (_edit_places->text().isEmpty()) {
		emit showMessage(tr("Не введены места!"));
		return false;
	}
	_data.setPlaces(_edit_places->text());

	return true;
}

void Trekking::WidgetData::save()
{
	if (copyGuiToData()) {
		emit saveData(_index, _data);
		close();
	}
}
