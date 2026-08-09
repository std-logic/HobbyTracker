#include "MainWindow.h"
#include "bike/widgets/BikeWidgetMain.h"
#include "books/widgets/BooksWidgetMain.h"
#include "coins/widgets/CoinsWidgetMain.h"
#include "concerts/widgets/ConcertsWidgetMain.h"
#include "flights/widgets/FlightsWidgetMain.h"
#include "games/widgets/GamesWidgetMain.h"
#include "movies/widgets/MoviesWidgetMain.h"
#include "music/widgets/MusicWidgetMain.h"
#include "player/widgets/PlayerWidgetMain.h"
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
	_coins->start();
	_concerts->start();
	_flights->start();
	_games->start();
	_movies->start();
	_music->start();
	_player->start();
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
	auto addTab = [this, central_widget](Base::WidgetMain* page, const QString& label) {
		central_widget->addTab(page, label);
		connect(page, &Base::WidgetMain::showMessage, this, &MainWindow::showMessage);
	};

	addTab(_music = new Music::WidgetMain, Music::WidgetMain::getName());
	addTab(_player = new Player::WidgetMain, Player::WidgetMain::getName());
	addTab(_movies = new Movies::WidgetMain, Movies::WidgetMain::getName());
	addTab(_books = new Books::WidgetMain, Books::WidgetMain::getName());
	addTab(_games = new Games::WidgetMain, Games::WidgetMain::getName());
	addTab(_coins = new Coins::WidgetMain, Coins::WidgetMain::getName());
	addTab(_concerts = new Concerts::WidgetMain, Concerts::WidgetMain::getName());
	addTab(_bike = new Bike::WidgetMain, Bike::WidgetMain::getName());
	addTab(_trekking = new Trekking::WidgetMain, Trekking::WidgetMain::getName());
	addTab(_flights = new Flights::WidgetMain, Flights::WidgetMain::getName());

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
