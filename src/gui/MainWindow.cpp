#include "MainWindow.h"
#include "books/widgets/BooksWidgetMain.h"
#include "games/widgets/GamesWidgetMain.h"

#include <QStatusBar>
#include <QTabWidget>

MainWindow::MainWindow(QWidget* parent)
	: QMainWindow{parent}
{
	initCommonParams();
	initStatusBar();
	initCentralWidget();
	initConnections();
}

void MainWindow::start()
{
	showDefaultTitle();

	_books->start();
	_games->start();

	show();
}

void MainWindow::dataCsv(const Csv::Settings& csv_settings, const Csv::Data& csv_data)
{
	_books->dataCsv(csv_settings, csv_data);
}

void MainWindow::initCommonParams()
{
	setMinimumSize(QSize(960, 540));
}

void MainWindow::initStatusBar()
{
	setStatusBar(new QStatusBar);
}

void MainWindow::initCentralWidget()
{
	auto central_widget = new QTabWidget(this);

	central_widget->addTab(_books = new Books::WidgetMain, Books::WidgetMain::getName());
	central_widget->addTab(_games = new Games::WidgetMain, Games::WidgetMain::getName());

	setCentralWidget(central_widget);
}

void MainWindow::initConnections()
{
	connect(_books, &Books::WidgetMain::readCsv,
			this, &MainWindow::readCsv);
}

void MainWindow::showDefaultTitle()
{
	setWindowTitle(tr("Трекер хобби"));
}
