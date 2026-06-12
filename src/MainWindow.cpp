#include "MainWindow.h"

MainWindow::MainWindow(QWidget* parent)
	: QMainWindow{parent}
{
	initCommonParams();
}

MainWindow::~MainWindow()
{
}

void MainWindow::initCommonParams()
{
	setMinimumSize(QSize(960, 540));
}
