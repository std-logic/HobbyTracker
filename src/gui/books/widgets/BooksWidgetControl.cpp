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
	_button_data_list->setChecked(true);
}

void Books::WidgetControl::highlightButtonSave(bool on)
{
	_button_save->highlight(on);
}

void Books::WidgetControl::initWidgets()
{
	// save
	{
		addWidget(_button_save = new Base::ButtonSave(this));
		connect(_button_save, &Base::ButtonSave::clicked,
				this, &WidgetControl::saveCsvData);
	}

	// data list
	{
		addSpacing();

		addWidget(_button_data_list = new Base::ButtonShow(tr("Список"), this));
		connect(_button_data_list, &Base::ButtonShow::toggled, this, [this](bool on) {
			_button_add_data->setEnabled(on);
			_button_collapse_data_list->setEnabled(on);
			_button_expand_data_list->setEnabled(on);
			_combo_data_list_view_mode->setEnabled(on);
			emit showDataList(on);
		});

		addWidget(_button_add_data = new Base::ButtonAdd(this));
		_button_add_data->setEnabled(false);
		connect(_button_add_data, &Base::ButtonAdd::clicked,
				this, &WidgetControl::addData);

		addWidget(_button_collapse_data_list = new Base::ButtonCollapse(this));
		_button_collapse_data_list->setEnabled(false);
		connect(_button_collapse_data_list, &Base::ButtonCollapse::clicked,
				this, &WidgetControl::collapseDataList);

		addWidget(_button_expand_data_list = new Base::ButtonExpand(this));
		_button_expand_data_list->setEnabled(false);
		connect(_button_expand_data_list, &Base::ButtonExpand::clicked,
				this, &WidgetControl::expandDataList);

		addWidget(_combo_data_list_view_mode = new QComboBox(this));
		_combo_data_list_view_mode->addItem(tr("По авторам"), static_cast<int>(DataListViewModes::ByAuthors));
		_combo_data_list_view_mode->addItem(tr("По жанрам"), static_cast<int>(DataListViewModes::ByGenres));
		_combo_data_list_view_mode->addItem(tr("По десятилетиям"), static_cast<int>(DataListViewModes::ByDecades));
		_combo_data_list_view_mode->addItem(tr("По столетиям"), static_cast<int>(DataListViewModes::ByCenturies));
		_combo_data_list_view_mode->addItem(tr("По оценкам"), static_cast<int>(DataListViewModes::ByRatings));
		_combo_data_list_view_mode->addItem(tr("Простой"), static_cast<int>(DataListViewModes::Simple));
		_combo_data_list_view_mode->setEnabled(false);
		connect(_combo_data_list_view_mode, &QComboBox::currentIndexChanged, this, [this](int index) {
			emit setDataListViewMode(_combo_data_list_view_mode->itemData(index).toInt());
		});
	}

	// extra list
	{
		addSpacing();

		addWidget(_button_extra_list = new Base::ButtonShow(tr("Дополнения"), this));
		connect(_button_extra_list, &Base::ButtonShow::toggled, this, [this](bool on) {
			_button_add_extra->setEnabled(on);
			_button_collapse_extra_list->setEnabled(on);
			_button_expand_extra_list->setEnabled(on);
			emit showExtraList(on);
		});

		addWidget(_button_add_extra = new Base::ButtonAdd(this));
		_button_add_extra->setEnabled(false);
		connect(_button_add_extra, &Base::ButtonAdd::clicked,
				this, &WidgetControl::addExtra);

		addWidget(_button_collapse_extra_list = new Base::ButtonCollapse(this));
		_button_collapse_extra_list->setEnabled(false);
		connect(_button_collapse_extra_list, &Base::ButtonCollapse::clicked,
				this, &WidgetControl::collapseExtraList);

		addWidget(_button_expand_extra_list = new Base::ButtonExpand(this));
		_button_expand_extra_list->setEnabled(false);
		connect(_button_expand_extra_list, &Base::ButtonExpand::clicked,
				this, &WidgetControl::expandExtraList);
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
