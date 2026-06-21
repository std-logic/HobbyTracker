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
	data.setAuthorTr("Айзек Азимов");
	data.setAuthorOrig("Isaac Asimov");
	data.setTitleTr("О времени, пространстве и других вещах");
	data.setTitleOrig("Of time and space and other things");
	data.setGenre("Научно-популярная");
	data.setYear(1965);
	data.setRating(4);
	_data_list.value().add(data);

	data.clear();
	data.setAuthorTr("Айзек Азимов");
	data.setAuthorOrig("Isaac Asimov");
	data.setTitleTr("Я, робот");
	data.setTitleOrig("I, robot");
	data.setGenre("Художественная");
	data.setYear(1950);
	data.setRating(8);
	_data_list.value().add(data);

	data.clear();
	data.setAuthorTr("Рикарду С. Аморим");
	data.setAuthorOrig("Ricardo S. Amorim");
	data.setTitleTr("Волки, которые были людьми. История Moonspell");
	data.setTitleOrig("Wolves who were men - The history of Moonspell");
	data.setGenre("Документальная");
	data.setYear(2021);
	data.setRating(9);
	_data_list.value().add(data);

	data.clear();
	data.setAuthorOrig("Светлана Алексиевич");
	data.setTitleOrig("У войны не женское лицо");
	data.setGenre("Документальная");
	data.setYear(1985);
	data.setRating(6);
	_data_list.value().add(data);

	data.clear();
	data.setAuthorOrig("Светлана Алексиевич");
	data.setTitleOrig("Время секонд хэнд");
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
