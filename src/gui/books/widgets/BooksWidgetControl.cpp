#include "BooksWidgetControl.h"
#include "../common/BooksCommon.h"

#include <gui/base/widgets/BaseButtonAdd.h>
#include <gui/base/widgets/BaseButtonCollapse.h>
#include <gui/base/widgets/BaseButtonExpand.h>
#include <gui/base/widgets/BaseButtonSave.h>
#include <gui/base/widgets/BaseButtonSettings.h>
#include <gui/base/widgets/BaseButtonShow.h>

#include <QLayout>
#include <QPushButton>
#include <QComboBox>

Books::WidgetControl::WidgetControl(QWidget* parent)
	: Base::WidgetControl{parent}
{
	initWidgets();
}

void Books::WidgetControl::start()
{
	_button_list->setChecked(true);
}

void Books::WidgetControl::initWidgets()
{
	// save
	{
		addWidget(_button_save = new Base::ButtonSave(this));
		connect(_button_save, &Base::ButtonSave::clicked,
				this, &WidgetControl::saveCsvData);
	}

	// list
	{
		addSpacing();

		addWidget(_button_list = new Base::ButtonShow(tr("Список"), this));
		connect(_button_list, &Base::ButtonShow::toggled, this, [this](bool on) {
			_button_add_data->setEnabled(on);
			_button_collapse_list->setEnabled(on);
			_button_expand_list->setEnabled(on);
			_combo_list_view_mode->setEnabled(on);
			emit showList(on);
		});

		addWidget(_button_add_data = new Base::ButtonAdd(this));
		_button_add_data->setEnabled(false);
		connect(_button_add_data, &Base::ButtonAdd::clicked,
				this, &WidgetControl::addData);

		addWidget(_button_collapse_list = new Base::ButtonCollapse(this));
		_button_collapse_list->setEnabled(false);
		connect(_button_collapse_list, &Base::ButtonCollapse::clicked,
				this, &WidgetControl::collapseList);

		addWidget(_button_expand_list = new Base::ButtonExpand(this));
		_button_expand_list->setEnabled(false);
		connect(_button_expand_list, &Base::ButtonExpand::clicked,
				this, &WidgetControl::expandList);

		addWidget(_combo_list_view_mode = new QComboBox(this));
		_combo_list_view_mode->addItem(tr("По авторам"), static_cast<int>(ListViewModes::ByAuthors));
		_combo_list_view_mode->addItem(tr("По жанрам"), static_cast<int>(ListViewModes::ByGenres));
		_combo_list_view_mode->addItem(tr("По десятилетиям"), static_cast<int>(ListViewModes::ByDecades));
		_combo_list_view_mode->addItem(tr("По столетиям"), static_cast<int>(ListViewModes::ByCenturies));
		_combo_list_view_mode->addItem(tr("По оценкам"), static_cast<int>(ListViewModes::ByRatings));
		_combo_list_view_mode->addItem(tr("Простой"), static_cast<int>(ListViewModes::Simple));
		_combo_list_view_mode->setEnabled(false);
		connect(_combo_list_view_mode, &QComboBox::currentIndexChanged, this, [this](int index) {
			emit setListViewMode(_combo_list_view_mode->itemData(index).toInt());
		});
	}

	// chart
	{
		addSpacing();

		addWidget(_button_chart = new Base::ButtonShow(tr("Статистика"), this));
		connect(_button_chart, &Base::ButtonShow::toggled, this, [this](bool on) {
			_combo_chart_view_mode->setEnabled(on);
			emit showChart(on);
		});

		addWidget(_combo_chart_view_mode = new QComboBox(this));
		_combo_chart_view_mode->addItem(tr("По десятилетиям"), static_cast<int>(ChartViewModes::ByDecades));
		_combo_chart_view_mode->addItem(tr("По столетиям"), static_cast<int>(ChartViewModes::ByCenturies));
		_combo_chart_view_mode->addItem(tr("По оценкам"), static_cast<int>(ChartViewModes::ByRatings));
		_combo_chart_view_mode->setEnabled(false);
		connect(_combo_chart_view_mode, &QComboBox::currentIndexChanged, this, [this](int index) {
			emit setChartViewMode(_combo_chart_view_mode->itemData(index).toInt());
		});
	}

	// settings
	{
		addStretch();

		addWidget(_button_settings = new Base::ButtonSettings(this));
		connect(_button_settings, &Base::ButtonSettings::clicked,
				this, &WidgetControl::showSettings);
	}
}
