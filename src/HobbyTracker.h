#pragma once

#include <memory>

class MainWindow;
class Storage;

class HobbyTracker
{
public:
	HobbyTracker();
	~HobbyTracker();

	void show();

private:
	void initConnections();

private:
	std::unique_ptr<MainWindow> _main_window;
	std::unique_ptr<Storage> _storage;
};
