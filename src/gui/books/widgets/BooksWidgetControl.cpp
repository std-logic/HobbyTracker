#include "BooksWidgetControl.h"
#include "../common/BooksCommon.h"

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
	}

	// list
	{
		addSpacing();

		addWidget(_button_list = new Base::ButtonShow(tr("Список"), this));
		connect(_button_list, &Base::ButtonShow::toggled, this, [this](bool on) {
			_button_collapse_list->setEnabled(on);
			_button_expand_list->setEnabled(on);
			_combo_list_view_mode->setEnabled(on);
			emit showList(on);
		});

		addWidget(_button_collapse_list = new Base::ButtonCollapse(this));
		connect(_button_collapse_list, &Base::ButtonCollapse::clicked,
				this, &WidgetControl::collapseList);

		addWidget(_button_expand_list = new Base::ButtonExpand(this));
		connect(_button_expand_list, &Base::ButtonExpand::clicked,
				this, &WidgetControl::expandList);

		addWidget(_combo_list_view_mode = new QComboBox(this));
		_combo_list_view_mode->addItem(tr("По авторам"), static_cast<int>(ListViewModes::ByAuthors));
		_combo_list_view_mode->addItem(tr("По жанрам"), static_cast<int>(ListViewModes::ByGenres));
		_combo_list_view_mode->addItem(tr("По десятилетиям"), static_cast<int>(ListViewModes::ByDecades));
		_combo_list_view_mode->addItem(tr("По столетиям"), static_cast<int>(ListViewModes::ByCenturies));
		_combo_list_view_mode->addItem(tr("По оценкам"), static_cast<int>(ListViewModes::ByRatings));
		_combo_list_view_mode->addItem(tr("Простой"), static_cast<int>(ListViewModes::Simple));
		connect(_combo_list_view_mode, &QComboBox::currentIndexChanged, this, [this](int index) {
			emit setListViewMode(_combo_list_view_mode->itemData(index).toInt());
		});
	}

	// statistics
	{
		addSpacing();

		addWidget(_button_statistics = new Base::ButtonShow(tr("Статистика"), this));
		connect(_button_statistics, &Base::ButtonShow::toggled,
				this, &WidgetControl::showStatistics);
	}

	// settings
	{
		addStretch();

		addWidget(_button_settings = new Base::ButtonSettings(this));
		connect(_button_settings, &Base::ButtonSettings::clicked,
				this, &WidgetControl::showSettings);
	}
}
