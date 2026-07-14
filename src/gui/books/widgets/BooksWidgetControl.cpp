#include "BooksWidgetControl.h"
#include "../common/BooksCommon.h"

Books::WidgetControl::WidgetControl(QWidget* parent)
	: Base::WidgetControl{parent}
{
	initWidgets();
}

void Books::WidgetControl::start()
{
	_button_data_list->setChecked(true);
}

void Books::WidgetControl::initWidgets()
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
				{tr("По авторам"), static_cast<int>(DataListViewModes::ByAuthors)},
				{tr("По жанрам"), static_cast<int>(DataListViewModes::ByGenres)},
				{tr("По десятилетиям"), static_cast<int>(DataListViewModes::ByDecades)},
				{tr("По столетиям"), static_cast<int>(DataListViewModes::ByCenturies)},
				{tr("По оценкам"), static_cast<int>(DataListViewModes::ByRatings)},
				{tr("Простой список"), static_cast<int>(DataListViewModes::Simple)},
		});

		_button_data_list->addSlaveWidgets({
			_button_add_data,
			_button_collapse_data_list,
			_button_expand_data_list,
			_combo_data_list_view_mode
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
			_button_expand_extra_list
		});
	}

	// chart
	{
		addSpacing();
		addButtonShow(_button_chart, tr("Статистика"), &WidgetControl::showChart);
		addComboBox(_combo_chart_view_mode, &WidgetControl::setChartViewMode, {
				{tr("По десятилетиям"), static_cast<int>(ChartViewModes::ByDecades)},
				{tr("По столетиям"), static_cast<int>(ChartViewModes::ByCenturies)},
				{tr("По оценкам"), static_cast<int>(ChartViewModes::ByRatings)}
		});

		_button_chart->addSlaveWidgets({
			_combo_chart_view_mode
		});
	}

	addButtonSettings();
}
