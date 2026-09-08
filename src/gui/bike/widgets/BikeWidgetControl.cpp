#include "BikeWidgetControl.h"
#include "../common/BikeCommon.h"

Bike::WidgetControl::WidgetControl(QWidget* parent)
	: Base::WidgetControl{parent}
{
	initWidgets();
}

void Bike::WidgetControl::start()
{
	_button_trip_list->setChecked(true);
}

void Bike::WidgetControl::initWidgets()
{
	addButtonSave();

	// trip list
	{
		addSpacing();
		addButtonShow(_button_trip_list, tr(" Велопоходы "), &WidgetControl::showTripList);
		addButtonAdd(_button_add_trip, &WidgetControl::addTrip);
		addButtonCollapse(_button_collapse_trip_list, &WidgetControl::collapseTripList);
		addButtonExpand(_button_expand_trip_list, &WidgetControl::expandTripList);
		addComboBox(_combo_trip_list_view_mode, &WidgetControl::setTripListViewMode, {
				{tr("Простой список"), static_cast<int>(DataListViewModes::Simple)},
				{tr("По странам"), static_cast<int>(DataListViewModes::ByCountries)},
		});

		_button_trip_list->addSlaveWidgets({
			_button_add_trip,
			_button_collapse_trip_list,
			_button_expand_trip_list,
			_combo_trip_list_view_mode,
		});
	}

	// data list
	{
		addSpacing();
		addButtonShow(_button_data_list, tr("Пробег"), &WidgetControl::showDataList);
		addButtonAdd(_button_add_data, &WidgetControl::addData);

		_button_data_list->addSlaveWidgets({
			_button_add_data,
		});
	}

	// chart
	{
		addSpacing();
		addButtonShow(_button_chart, tr("Статистика"), &WidgetControl::showChart);
		addComboBox(_combo_chart_view_mode, &WidgetControl::setChartViewMode, {
				{tr("По велопоходам"), static_cast<int>(ChartViewModes::ByTrips)},
				{tr("По странам"), static_cast<int>(ChartViewModes::ByCountries)},
				{tr("По километрам пробега"), static_cast<int>(ChartViewModes::ByDist)},
				{tr("По часам пробега"), static_cast<int>(ChartViewModes::ByTime)},
		});

		_button_chart->addSlaveWidgets({
			_combo_chart_view_mode,
		});
	}

	addStretch();
	addEditSearch();
	addButtonSettings();
}
