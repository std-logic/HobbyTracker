#include "MoviesWidgetControl.h"
#include "../common/MoviesCommon.h"

#include <QCheckBox>

Movies::WidgetControl::WidgetControl(QWidget* parent)
	: Base::WidgetControl{parent}
{
	initWidgets();
}

void Movies::WidgetControl::start()
{
	_button_data_list->setChecked(true);
}

void Movies::WidgetControl::initWidgets()
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
				{tr("Простой список"), static_cast<int>(DataListViewModes::Simple)},
				{tr("По типам"), static_cast<int>(DataListViewModes::ByKinds)},
				{tr("По жанрам"), static_cast<int>(DataListViewModes::ByGenres)},
				{tr("По странам"), static_cast<int>(DataListViewModes::ByCountries)},
				{tr("По регионам"), static_cast<int>(DataListViewModes::ByRegions)},
				{tr("По годам"), static_cast<int>(DataListViewModes::ByYears)},
				{tr("По десятилетиям"), static_cast<int>(DataListViewModes::ByDecades)},
				{tr("По режиссёрам"), static_cast<int>(DataListViewModes::ByDirectors)},
				{tr("По сценаристам"), static_cast<int>(DataListViewModes::ByWriters)},
				{tr("По актёрам"), static_cast<int>(DataListViewModes::ByActors)},
				{tr("По оценкам"), static_cast<int>(DataListViewModes::ByRatings)},
		});

		_button_data_list->addSlaveWidgets({
			_button_add_data,
			_button_collapse_data_list,
			_button_expand_data_list,
			_combo_data_list_view_mode,
		});
	}

	// extra list
	{
		addSpacing();
		addButtonShow(_button_extra_list, tr(" Дополнения "), &WidgetControl::showExtraList);
		addButtonAdd(_button_add_extra, &WidgetControl::addExtra);
		addButtonCollapse(_button_collapse_extra_list, &WidgetControl::collapseExtraList);
		addButtonExpand(_button_expand_extra_list, &WidgetControl::expandExtraList);

		_button_extra_list->addSlaveWidgets({
			_button_add_extra,
			_button_collapse_extra_list,
			_button_expand_extra_list,
		});
	}

	// chart
	{
		addSpacing();
		addButtonShow(_button_chart, tr("Статистика"), &WidgetControl::showChart);
		addComboBox(_combo_chart_view_mode, &WidgetControl::setChartViewMode, {
				{tr("По годам просмотра"), static_cast<int>(ChartViewModes::ByViewDates)},
				{tr("По жанрам"), static_cast<int>(ChartViewModes::ByGenres)},
				{tr("По странам"), static_cast<int>(ChartViewModes::ByCountries)},
				{tr("По регионам"), static_cast<int>(ChartViewModes::ByRegions)},
				{tr("По годам"), static_cast<int>(ChartViewModes::ByYears)},
				{tr("По десятилетиям"), static_cast<int>(ChartViewModes::ByDecades)},
				{tr("По режиссёрам"), static_cast<int>(ChartViewModes::ByDirectors)},
				{tr("По сценаристам"), static_cast<int>(ChartViewModes::ByWriters)},
				{tr("По актёрам"), static_cast<int>(ChartViewModes::ByActors)},
				{tr("По оценкам"), static_cast<int>(ChartViewModes::ByRatings)},
		});

		_button_chart->addSlaveWidgets({
			_combo_chart_view_mode,
		});
	}

	addSpacing();
	addCheckBox(_check_favorites, tr("Только избранные"), &WidgetControl::setFavoritesOnly);

	addButtonSettings();
}
