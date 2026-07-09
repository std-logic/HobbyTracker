#include "TrekkingWidgetControl.h"
#include "../common/TrekkingCommon.h"

#include <gui/base/widgets/BaseButtonAdd.h>
#include <gui/base/widgets/BaseButtonCollapse.h>
#include <gui/base/widgets/BaseButtonExpand.h>
#include <gui/base/widgets/BaseButtonShow.h>

#include <QLayout>
#include <QPushButton>
#include <QComboBox>

Trekking::WidgetControl::WidgetControl(QWidget* parent)
	: Base::WidgetControl{parent}
{
	initWidgets();
}

void Trekking::WidgetControl::start()
{
	_button_data_list->setChecked(true);
}

void Trekking::WidgetControl::initWidgets()
{
	addButtonSave();

	// data list
	{
		addSpacing();

		addWidget(_button_data_list = new Base::ButtonShow(tr("Список"), this));
		connect(_button_data_list, &Base::ButtonShow::toggled,
				this, &WidgetControl::showDataList);

		addWidget(_button_add_data = new Base::ButtonAdd(this));
		connect(_button_add_data, &Base::ButtonAdd::clicked,
				this, &WidgetControl::addData);

		addWidget(_button_collapse_data_list = new Base::ButtonCollapse(this));
		connect(_button_collapse_data_list, &Base::ButtonCollapse::clicked,
				this, &WidgetControl::collapseDataList);

		addWidget(_button_expand_data_list = new Base::ButtonExpand(this));
		connect(_button_expand_data_list, &Base::ButtonExpand::clicked,
				this, &WidgetControl::expandDataList);

		addWidget(_combo_data_list_view_mode = new QComboBox(this));
		_combo_data_list_view_mode->addItem(tr("Простой список"), static_cast<int>(DataListViewModes::Simple));
		_combo_data_list_view_mode->addItem(tr("По странам"), static_cast<int>(DataListViewModes::ByCountries));
		_combo_data_list_view_mode->addItem(tr("По типам"), static_cast<int>(DataListViewModes::ByKinds));
		connect(_combo_data_list_view_mode, &QComboBox::currentIndexChanged, this, [this](int index) {
			emit setDataListViewMode(_combo_data_list_view_mode->itemData(index).toInt());
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

		addWidget(_button_chart = new Base::ButtonShow(tr("Статистика"), this));
		connect(_button_chart, &Base::ButtonShow::toggled,
				this, &WidgetControl::showChart);
	}

	addButtonSettings();
}
