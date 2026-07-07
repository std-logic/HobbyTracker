#include "BikeWidgetControl.h"
#include "../common/BikeCommon.h"

#include <gui/base/widgets/BaseButtonAdd.h>
#include <gui/base/widgets/BaseButtonShow.h>

#include <QLayout>
#include <QPushButton>
#include <QComboBox>

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

		addWidget(_button_data_list = new Base::ButtonShow(tr("Список"), this));
		connect(_button_data_list, &Base::ButtonShow::toggled,
				this, &WidgetControl::showDataList);

		addWidget(_button_add_data = new Base::ButtonAdd(this));
		connect(_button_add_data, &Base::ButtonAdd::clicked,
				this, &WidgetControl::addData);

		_button_data_list->addSlaveWidgets({
			_button_add_data,
		});
	}

	// chart
	{
		addSpacing();

		addWidget(_button_chart = new Base::ButtonShow(tr("Статистика"), this));
		connect(_button_chart, &Base::ButtonShow::toggled,
				this, &WidgetControl::showChart);

		addWidget(_combo_chart_view_mode = new QComboBox(this));
		_combo_chart_view_mode->addItem(tr("Пробеги"), static_cast<int>(ChartViewModes::ByDist));
		_combo_chart_view_mode->addItem(tr("Время"), static_cast<int>(ChartViewModes::ByTime));
		connect(_combo_chart_view_mode, &QComboBox::currentIndexChanged, this, [this](int index) {
			emit setChartViewMode(_combo_chart_view_mode->itemData(index).toInt());
		});

		_button_chart->addSlaveWidgets({
			_combo_chart_view_mode
		});
	}

	addButtonSettings();
}
