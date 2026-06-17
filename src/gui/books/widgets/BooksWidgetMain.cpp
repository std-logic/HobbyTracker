#include "BooksWidgetMain.h"
#include "BooksWidgetControl.h"
#include "BooksWidgetList.h"
#include "BooksWidgetStatistics.h"

Books::WidgetMain::WidgetMain(QWidget* parent)
	: Base::WidgetMain{parent}
{
	initGui();
	initConnections();
}

void Books::WidgetMain::start()
{
	_control->start();

	// test!!!!
	_data_list = DataList();
	Data data;
	data.setAuthor("Айзек Азимов (Isaac Asimov)");
	data.setTitle("О времени, пространстве и других вещах (Of time and space and other things)");
	data.setGenre("Научно-популярная");
	data.setYear(1965);
	data.setRating(4);
	_data_list.value().add(data);
	data.setAuthor("Айзек Азимов (Isaac Asimov)");
	data.setTitle("Я, робот (I, robot)");
	data.setGenre("Художественная");
	data.setYear(1950);
	data.setRating(8);
	_data_list.value().add(data);
	data.setAuthor("Рикарду С. Аморим (Ricardo S. Amorim)");
	data.setTitle("Волки, которые были людьми. История Moonspell (Wolves who were men - The history of Moonspell)");
	data.setGenre("Документальная");
	data.setYear(2021);
	data.setRating(9);
	_data_list.value().add(data);
	data.setAuthor("Светлана Алексиевич");
	data.setTitle("У войны не женское лицо");
	data.setGenre("Документальная");
	data.setYear(1985);
	data.setRating(6);
	_data_list.value().add(data);
	data.setAuthor("Светлана Алексиевич");
	data.setTitle("Время секонд хэнд");
	data.setGenre("Документальная");
	data.setYear(2013);
	data.setRating(5);
	_data_list.value().add(data);
	_list->showList(_data_list.value());
	// test!!!!
}

void Books::WidgetMain::initGui()
{
	addWidget(_control = new WidgetControl(this), 0, Qt::AlignTop);

	addWidget(_list = new WidgetList(this));

	addWidget(_statistics = new WidgetStatistics(this));
}

void Books::WidgetMain::initConnections()
{
	connect(_control, &WidgetControl::showList,
			_list, &WidgetList::setVisible);
	connect(_control, &WidgetControl::listModeChanged,
			_list, &WidgetList::setViewMode);

	connect(_control, &WidgetControl::showStatistics,
			_statistics, &WidgetList::setVisible);

	connect(_list, &WidgetList::needUpdate,
			this, &WidgetMain::updateList);
}

void Books::WidgetMain::updateList()
{
	if (_data_list.has_value()) {
		_list->showList(_data_list.value());
	}
}
