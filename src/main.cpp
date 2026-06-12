#include "HobbyTracker.h"

#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	HobbyTracker hobby_tracker;
	hobby_tracker.show();

	return app.exec();
}
