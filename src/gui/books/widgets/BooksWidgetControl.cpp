#include "BooksWidgetControl.h"
#include "../common/BooksCommon.h"

#include <gui/base/widgets/BaseButtonSave.h>
#include <gui/base/widgets/BaseButtonSettings.h>
#include <gui/base/widgets/BaseButtonShow.h>

#include <QLayout>
#include <QPushButton>
#include <QComboBox>

Books::WidgetControl::WidgetControl(QWidget* parent)
	: Base::WidgetControl{parent}
{
	initGui();
}

void Books::WidgetControl::start()
{
	_button_list->setChecked(true);
}

void Books::WidgetControl::initGui()
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
			_combo_list_mode->setEnabled(on);
			emit showList(on);
		});

		addWidget(_combo_list_mode = new QComboBox(this));
		_combo_list_mode->addItem(tr("По авторам"), static_cast<int>(ListViewModes::ByAuthors));
		_combo_list_mode->addItem(tr("По жанрам"), static_cast<int>(ListViewModes::ByGenres));
		_combo_list_mode->addItem(tr("По десятилетиям"), static_cast<int>(ListViewModes::ByDecades));
		_combo_list_mode->addItem(tr("По столетиям"), static_cast<int>(ListViewModes::ByCenturies));
		_combo_list_mode->addItem(tr("По оценкам"), static_cast<int>(ListViewModes::ByRatings));
		_combo_list_mode->addItem(tr("Простой"), static_cast<int>(ListViewModes::Simple));
		connect(_combo_list_mode, &QComboBox::currentIndexChanged,
				this, &WidgetControl::listModeChanged);
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
	}
}
