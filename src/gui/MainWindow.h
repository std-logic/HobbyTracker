#pragma once

#include <QMainWindow>

#include <QElapsedTimer>

namespace Books { class WidgetMain; }
namespace Games { class WidgetMain; }

class MainWindow : public QMainWindow
{
	Q_OBJECT
public:
	explicit MainWindow(QWidget* parent = nullptr);
	~MainWindow() = default;

	void start();

public slots:

signals:

private:
	void initCommonParams();
	void initStatusBar();
	void initCentralWidget();
	void initConnections();

	void showDefaultTitle();
	void showLoadingStart();
	void showLoadingFinish();

private:
	Books::WidgetMain* _books;
	Games::WidgetMain* _games;

	QElapsedTimer _loading_timer;
};
