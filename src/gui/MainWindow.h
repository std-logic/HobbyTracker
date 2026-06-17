#pragma once

#include <QMainWindow>

namespace Books { class WidgetMain; }
namespace Games { class WidgetMain; }

class MainWindow : public QMainWindow
{
	Q_OBJECT
public:
	explicit MainWindow(QWidget* parent = nullptr);
	~MainWindow() = default;

signals:

private:
	void initCommonParams();
	void initStatusBar();
	void initCentralWidget();

	void showDefaultTitle();
	void start();


private:
	Books::WidgetMain* _books;
	Games::WidgetMain* _games;
};
