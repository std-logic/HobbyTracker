#include "BooksWidgetMain.h"
#include "BooksWidgetControl.h"
#include "BooksWidgetList.h"
#include "BooksWidgetStatistics.h"
#include "../data/BooksConverter.h"

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
	Csv::Settings settings;
	settings.setFileName("hobby_books_data.csv");
	settings.setEncoding(QStringConverter::Utf8);
	settings.setDelimiter(';');
	settings.setSkipAtStart(1);
	settings.setHeader({
		tr("Автор (пер.)"), tr("Автор (ориг.)"),
		tr("Произведение (пер.)"), tr("Произведение (ориг.)"),
		tr("Жанр"), tr("Год"), tr("Оценка")
   });
	_settings.setCsvSettings(settings);

	emit readCsv(_settings.csvSettings());
	// test!!!!
}

void Books::WidgetMain::dataCsv(const Csv::Settings& csv_settings, const Csv::Data& csv_data)
{
	if (!_settings.isCsvFileNameEqual(csv_settings.fileName())) {
		return;
	}

	_csv_data = csv_data;
	_data_list = Converter::conv(csv_data);

	_list->showList(_data_list.value());
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
	connect(_control, &WidgetControl::collapseList,
			_list, &WidgetList::collapseAll);
	connect(_control, &WidgetControl::expandList,
			_list, &WidgetList::expandAll);
	connect(_control, &WidgetControl::setListViewMode,
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
