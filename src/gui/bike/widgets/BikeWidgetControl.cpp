#include "BikeWidgetControl.h"
#include "../common/BikeCommon.h"

Bike::WidgetControl::WidgetControl(QWidget* parent)
	: Base::WidgetControl{parent}
{
	initWidgets();
}

void Bike::WidgetControl::start()
{
	_button_data_list->setChecked(true);
}

void Bike::WidgetControl::initWidgets()
{
	addButtonSave();

	// data list
	{
		addSpacing();
		addButtonShow(_button_data_list, tr("Пробег"), &WidgetControl::showDataList);
		addButtonAdd(_button_add_data, &WidgetControl::addData);

		_button_data_list->addSlaveWidgets({
			_button_add_data,
		});
	}

	// trip list
	{
		addSpacing();
		addButtonShow(_button_trip_list, tr(" Велопоходы "), &WidgetControl::showTripList);
		addButtonAdd(_button_add_trip, &WidgetControl::addTrip);

		_button_trip_list->addSlaveWidgets({
			_button_add_trip,
		});
	}

	// chart
	{
		addSpacing();
		addButtonShow(_button_chart, tr("Статистика"), &WidgetControl::showChart);
		addComboBox(_combo_chart_view_mode, &WidgetControl::setChartViewMode, {
				{tr("По километрам"), static_cast<int>(ChartViewModes::ByDist)},
				{tr("По часам"), static_cast<int>(ChartViewModes::ByTime)},
				{tr("По велопоходам"), static_cast<int>(ChartViewModes::ByTrips)}
		});

		_button_chart->addSlaveWidgets({
			_combo_chart_view_mode
		});
	}

	addButtonSettings();
}
