#include "HobbyTracker.h"

#include <common/Helper.h>

#include <QApplication>
#include <QResource>

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	QCoreApplication::setOrganizationName("std_logic");
	QCoreApplication::setApplicationName("HobbyTracker");

	QResource::registerResource(Helper::stdPath(Global::flags_file_name));

	HobbyTracker hobby_tracker;
	hobby_tracker.show();

	return app.exec();
}
