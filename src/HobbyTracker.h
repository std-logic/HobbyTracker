#pragma once

#include <memory>

class MainWindow;

class HobbyTracker
{
public:
	HobbyTracker();
	~HobbyTracker();

	void show();

private:
	std::unique_ptr<MainWindow> _main_window;
};
