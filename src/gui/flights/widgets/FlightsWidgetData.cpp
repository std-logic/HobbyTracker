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
		connect(_widgets_point[i].combo_airport, &Base::ComboEdit::currentTextChanged,
				this, [this, i](const QString& airport) { airportChanged(i, airport); });
	}
}

void Flights::WidgetData::initData()
{
	if (_mode_edit_data) { _data = _data_list[_index]; }
	// saving distances between all known airports for future fast access to them
	_dist_list = _data_list.distList();
}

void Flights::WidgetData::initCommonParams()
{
	setWindowTitle(_mode_edit_data ?
			tr("Редактирование полёта") :
			tr("Добавление нового полёта"));
	setMinimumWidth(500);
}

void Flights::WidgetData::initWidgets()
{
	add(tr("Дата:"), _edit_date);
	_edit_date->setPlaceholderText(tr("YYYY.MM.DD"));

	auto layout_head = new QHBoxLayout();
	layout_head->setContentsMargins(0, 0, 0, 0);
	layout_head->setSpacing(Global::Sizes::default_spacing);

	auto label_country = new QLabel(tr("Страна:"), this);
	label_country->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
	layout_head->addWidget(label_country, 2);

	auto label_city = new QLabel(tr("Город:"), this);
	label_city->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
	layout_head->addWidget(label_city, 2);

	auto label_airport = new QLabel(tr("Аэропорт:"), this);
	label_airport->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
	layout_head->addWidget(label_airport, 1);

	auto label_dist = new QLabel(tr("Километров:"), this);
	label_dist->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
	layout_head->addWidget(label_dist, 1);

	addLayout(layout_head);

	for (size_t i = 0; i < max_points_num; ++i) {
		auto layout_point = new QHBoxLayout();
		layout_point->setContentsMargins(0, 0, 0, 0);
		layout_point->setSpacing(Global::Sizes::default_spacing);

		_widgets_point[i].combo_country = new Base::ComboEdit(this);
		// _widgets_point[i].combo_country->setFixedWidth(150);
		layout_point->addWidget(_widgets_point[i].combo_country, 2);

		_widgets_point[i].combo_city = new Base::ComboEdit(this);
		// _widgets_point[i].combo_city->setFixedWidth(150);
		layout_point->addWidget(_widgets_point[i].combo_city, 2);

		_widgets_point[i].combo_airport = new Base::ComboEdit(this);
		// _widgets_point[i].combo_airport->setFixedWidth(60);
		layout_point->addWidget(_widgets_point[i].combo_airport, 1);

		_widgets_point[i].edit_dist = new QLineEdit(QStringLiteral("0"), this);
		// _widgets_point[i].edit_dist->setFixedWidth(60);
		layout_point->addWidget(_widgets_point[i].edit_dist, 1);

		addLayout(layout_point);
	}

	_widgets_point[0].edit_dist->setEnabled(false);
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

			_widgets_point[i].edit_dist->setText(QString::number(_data.dist(i)));
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
				_widgets_point[i].combo_airport->currentText(),
				_widgets_point[i].edit_dist->text().toUInt()
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

void Flights::WidgetData::airportChanged(size_t point, const QString& airport)
{
	if (point > 0) {
		QString prev_airport = _widgets_point[point-1].combo_airport->currentText();
		if (!prev_airport.isEmpty()) {
			QString dist_list_key = prev_airport + airport;
			if (_dist_list.contains(dist_list_key)) {
				uint32_t dist = _dist_list[dist_list_key];
				if (dist > 0) {
					_widgets_point[point].edit_dist->setText(QString::number(dist));
				}
			}
		}
	}
	if (point < (max_points_num - 1)) {
		QString next_airport = _widgets_point[point+1].combo_airport->currentText();
		if (!next_airport.isEmpty()) {
			QString dist_list_key = airport + next_airport;
			if (_dist_list.contains(dist_list_key)) {
				uint32_t dist = _dist_list[dist_list_key];
				if (dist > 0) {
					_widgets_point[point+1].edit_dist->setText(QString::number(dist));
				}
			}
		}
	}
}
