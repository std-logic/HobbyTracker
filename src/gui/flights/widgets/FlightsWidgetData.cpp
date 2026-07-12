#include "FlightsWidgetData.h"

#include <gui/base/widgets/BaseComboEdit.h>

#include <QLineEdit>
#include <QGroupBox>
#include <QLabel>
#include <QHBoxLayout>

Flights::WidgetData::WidgetData(size_t index, const DataList& data_list, QWidget* parent)
	: Base::WidgetData{index, data_list.size(), parent}
	, _data_list{data_list}
{
	initData();
	initCommonParams();
	initWidgets();
	copyDataToGui();

	// strictly after initialization finished, because we need only real changes
	for (size_t i = 0; i < max_points_num; ++i) {
		connect(_widgets_point[i].combo_country, &Base::ComboEdit::currentTextChanged,
				this, [this, i](const QString& country) { countryChanged(i, country); });
		connect(_widgets_point[i].combo_city, &Base::ComboEdit::currentTextChanged,
				this, [this, i](const QString& city) { cityChanged(i, city); });
	}
}

void Flights::WidgetData::initData()
{
	if (_mode_edit_data) { _data = _data_list[_index]; }
}

void Flights::WidgetData::initCommonParams()
{
	setWindowTitle(_mode_edit_data ?
			tr("Редактирование полёта") :
			tr("Добавление нового полёта"));
	setMinimumWidth(550);
}

void Flights::WidgetData::initWidgets()
{
	addWidget(tr("Дата:"), _edit_date = new QLineEdit(this));
	_edit_date->setPlaceholderText(tr("YYYY.MM.DD"));

	for (size_t i = 0; i < max_points_num; ++i) {
		auto layout_point = new QHBoxLayout();
		layout_point->setContentsMargins(0, 0, 0, 0);
		layout_point->setSpacing(Global::Sizes::default_spacing);

		auto label_country = new QLabel(tr("Страна:"), this);
		label_country->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
		layout_point->addWidget(label_country, 0);

		_widgets_point[i].combo_country = new Base::ComboEdit(this);
		_widgets_point[i].combo_country->setFixedWidth(150);
		layout_point->addWidget(_widgets_point[i].combo_country);

		auto label_city = new QLabel(tr("Город:"), this);
		label_city->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
		layout_point->addWidget(label_city, 2);

		_widgets_point[i].combo_city = new Base::ComboEdit(this);
		_widgets_point[i].combo_city->setFixedWidth(150);
		layout_point->addWidget(_widgets_point[i].combo_city);

		auto label_airport = new QLabel(tr("Аэропорт:"), this);
		label_airport->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
		layout_point->addWidget(label_airport, 3);

		_widgets_point[i].combo_airport = new Base::ComboEdit(this);
		_widgets_point[i].combo_airport->setFixedWidth(60);
		layout_point->addWidget(_widgets_point[i].combo_airport);

		addLayout(layout_point);
	}
}

void Flights::WidgetData::copyDataToGui()
{
	_edit_date->setText(_data.date());

	auto list_of_countries = _data_list.listOfCountries();

	for (size_t i = 0; i < max_points_num; ++i) {
		_widgets_point[i].combo_country->addList(list_of_countries);

		if (i < _data.pointsNum()) {
			_widgets_point[i].combo_country->lineEdit()->setText(_data.country(i));

			_widgets_point[i].combo_city->setTextAndList(
					_data.city(i), _data_list.listOfCities(_data.country(i)));

			_widgets_point[i].combo_airport->setTextAndList(
					_data.airport(i), _data_list.listOfAirports(_data.city(i)));
		}
	}
}

bool Flights::WidgetData::copyGuiToData()
{
	if (_edit_date->text().isEmpty()) {
		emit showMessage(tr("Не введена дата!"));
		return false;
	}
	_data.setDate(_edit_date->text());

	Data::FlightPoints points;
	for (size_t i = 0; i < max_points_num; ++i) {
		if ((_widgets_point[i].combo_country->currentText().isEmpty()) ||
			(_widgets_point[i].combo_city->currentText().isEmpty()) ||
			(_widgets_point[i].combo_airport->currentText().isEmpty())) {
			if (i < 2) {
				emit showMessage(tr("Полёт должен содержать как минимум 2 точки!"));
				return false;
			} else {
				break;
			}
		}
		points.emplace_back(
				_widgets_point[i].combo_country->currentText(),
				_widgets_point[i].combo_city->currentText(),
				_widgets_point[i].combo_airport->currentText()
		);
	}
	_data.setPoints(points);

	return true;
}

void Flights::WidgetData::save()
{
	if (copyGuiToData()) {
		emit saveData(_index, _data);
		close();
	}
}

void Flights::WidgetData::countryChanged(size_t point, const QString& country)
{
	if (!country.isEmpty() && (_widgets_point[point].combo_country->findText(country) >= 0)) {
		_widgets_point[point].combo_city->addList(_data_list.listOfCities(country));
	} else {
		_widgets_point[point].combo_city->clear();
	}
}

void Flights::WidgetData::cityChanged(size_t point, const QString& city)
{
	if (!city.isEmpty() && (_widgets_point[point].combo_city->findText(city) >= 0)) {
		_widgets_point[point].combo_airport->addList(_data_list.listOfAirports(city));
	} else {
		_widgets_point[point].combo_airport->clear();
	}
}
