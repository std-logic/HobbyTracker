#include "HobbyTracker.h"
#include "gui/MainWindow.h"

HobbyTracker::HobbyTracker()
	: _main_window{std::make_unique<MainWindow>()}
{
}

HobbyTracker::~HobbyTracker()
{
}

void HobbyTracker::show()
{
	_main_window->start();
}
