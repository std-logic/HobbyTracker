#include "BaseSettings.h"

#include <QCoreApplication>

Base::Settings::Settings()
{
}

QString Base::Settings::fullPath(const QString& file_name) const
{
	return QCoreApplication::applicationDirPath() + '/' + file_name;
}
