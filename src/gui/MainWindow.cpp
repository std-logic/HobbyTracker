#include "MainWindow.h"
#include "bike/widgets/BikeWidgetMain.h"
#include "books/widgets/BooksWidgetMain.h"
#include "flights/widgets/FlightsWidgetMain.h"
#include "games/widgets/GamesWidgetMain.h"
#include "trekking/widgets/TrekkingWidgetMain.h"

#include <common/Global.h>

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
	showLoadingStart();

	_bike->start();
	_books->start();
	_flights->start();
	_games->start();
	_trekking->start();

	showLoadingFinish();
	show();
}

void MainWindow::initCommonParams()
{
	setMinimumSize(Global::Sizes::window_min_width, Global::Sizes::window_min_height);

	QFont default_font = font();
	default_font.setPointSize(Global::Sizes::font_small);
	setFont(default_font);
}

void MainWindow::initStatusBar()
{
	setStatusBar(new QStatusBar);
}

void MainWindow::initCentralWidget()
{
	auto central_widget = new QTabWidget(this);

	central_widget->addTab(_books = new Books::WidgetMain, Books::WidgetMain::getName());
	connect(_books, &Books::WidgetMain::showMessage, this, &MainWindow::showMessage);

	central_widget->addTab(_games = new Games::WidgetMain, Games::WidgetMain::getName());
	connect(_games, &Games::WidgetMain::showMessage, this, &MainWindow::showMessage);

	central_widget->addTab(_bike = new Bike::WidgetMain, Bike::WidgetMain::getName());
	connect(_bike, &Bike::WidgetMain::showMessage, this, &MainWindow::showMessage);

	central_widget->addTab(_trekking = new Trekking::WidgetMain, Trekking::WidgetMain::getName());
	connect(_trekking, &Trekking::WidgetMain::showMessage, this, &MainWindow::showMessage);

	central_widget->addTab(_flights = new Flights::WidgetMain, Flights::WidgetMain::getName());
	connect(_flights, &Flights::WidgetMain::showMessage, this, &MainWindow::showMessage);

	setCentralWidget(central_widget);
}

void MainWindow::initConnections()
{
}

void MainWindow::showDefaultTitle()
{
	setWindowTitle(tr("Трекер хобби"));
}

void MainWindow::showLoadingStart()
{
	_loading_timer.start();
}

void MainWindow::showLoadingFinish()
{
	showMessage(tr("Базы данных загружены за %1 мс").arg(_loading_timer.elapsed()), 10000);
}

void MainWindow::showMessage(const QString& text, int timeout)
{
	statusBar()->showMessage(text, timeout);
}
