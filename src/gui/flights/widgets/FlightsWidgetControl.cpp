#include "FlightsWidgetControl.h"
#include "../common/FlightsCommon.h"

Flights::WidgetControl::WidgetControl(QWidget* parent)
	: Base::WidgetControl{parent}
{
	initWidgets();
}

void Flights::WidgetControl::start()
{
	_button_data_list->setChecked(true);
}

void Flights::WidgetControl::initWidgets()
{
	addButtonSave();

	// data list
	{
		addSpacing();
		addButtonShow(_button_data_list, tr("Список"), &WidgetControl::showDataList);
		addButtonAdd(_button_add_data, &WidgetControl::addData);
		addButtonCollapse(_button_collapse_data_list, &WidgetControl::collapseDataList);
		addButtonExpand(_button_expand_data_list, &WidgetControl::expandDataList);
		addComboBox(_combo_data_list_view_mode, &WidgetControl::setDataListViewMode, {
				{tr("По годам"), static_cast<int>(DataListViewModes::ByYears)},
				{tr("По странам"), static_cast<int>(DataListViewModes::ByCountries)},
				{tr("По городам"), static_cast<int>(DataListViewModes::ByCities)},
				{tr("По аэропортам"), static_cast<int>(DataListViewModes::ByAirports)},
				{tr("По маршрутам"), static_cast<int>(DataListViewModes::ByRoutes)},
				{tr("Полное древо"), static_cast<int>(DataListViewModes::AirportsTree)},
				{tr("Простой список"), static_cast<int>(DataListViewModes::Simple)},
		});

		_button_data_list->addSlaveWidgets({
			_button_add_data,
			_button_collapse_data_list,
			_button_expand_data_list,
			_combo_data_list_view_mode,
		});
	}

	// chart
	{
		addSpacing();
		addButtonShow(_button_chart, tr("Статистика"), &WidgetControl::showChart);
	}

	addButtonSettings();
}
