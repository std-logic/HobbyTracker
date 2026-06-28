#include "MainWindow.h"
#include "books/widgets/BooksWidgetMain.h"
#include "games/widgets/GamesWidgetMain.h"

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

	_books->start();
	_games->start();

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
	central_widget->addTab(_games = new Games::WidgetMain, Games::WidgetMain::getName());

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
	statusBar()->showMessage(tr("Базы данных загружены за %1 мс")
							 .arg(_loading_timer.elapsed()), 10000);
}
