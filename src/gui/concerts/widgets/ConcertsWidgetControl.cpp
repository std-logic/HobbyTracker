#include "ConcertsWidgetControl.h"
#include "../common/ConcertsCommon.h"

#include <QCheckBox>

Concerts::WidgetControl::WidgetControl(QWidget* parent)
	: Base::WidgetControl{parent}
{
	initWidgets();
}

void Concerts::WidgetControl::start()
{
	_button_data_list->setChecked(true);
}

void Concerts::WidgetControl::initWidgets()
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
				{tr("По группам"), static_cast<int>(DataListViewModes::ByArtists)},
				{tr("По типам"), static_cast<int>(DataListViewModes::ByTags)},
				{tr("По странам"), static_cast<int>(DataListViewModes::ByCountries)},
				{tr("По городам"), static_cast<int>(DataListViewModes::ByCities)},
				{tr("По местам"), static_cast<int>(DataListViewModes::ByPlaces)},
				{tr("Полное древо"), static_cast<int>(DataListViewModes::PlacesTree)},
				{tr("Простой список"), static_cast<int>(DataListViewModes::Simple)},
		});
		addCheckBox(_check_favorites, tr("Только избранные"), &WidgetControl::setFavoritesState);

		_button_data_list->addSlaveWidgets({
			_button_add_data,
			_button_collapse_data_list,
			_button_expand_data_list,
			_combo_data_list_view_mode,
			_check_favorites,
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
	}

	addButtonSettings();
}
