#include "HobbyTracker.h"
#include "gui/MainWindow.h"
#include "storage/Storage.h"

HobbyTracker::HobbyTracker()
	: _main_window{std::make_unique<MainWindow>()}
	, _storage{std::make_unique<Storage>()}
{
	initConnections();
}

HobbyTracker::~HobbyTracker()
{
}

void HobbyTracker::show()
{
	_main_window->start();
}

void HobbyTracker::initConnections()
{
	QObject::connect(_main_window.get(), &MainWindow::readCsv,
					 _storage.get(), &Storage::readCsv);
	QObject::connect(_storage.get(), &Storage::dataCsv,
					 _main_window.get(), &MainWindow::dataCsv);
}
