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

	start();
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

void MainWindow::showDefaultTitle()
{
	setWindowTitle(tr("Трекер хобби"));
}

void MainWindow::start()
{
	showDefaultTitle();

	_books->start();
	_games->start();
}
