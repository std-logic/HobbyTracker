#pragma once

#include <QMainWindow>

#include <QElapsedTimer>

namespace Bike { class WidgetMain; }
namespace Books { class WidgetMain; }
namespace Games { class WidgetMain; }
namespace Trekking { class WidgetMain; }

class MainWindow : public QMainWindow
{
	Q_OBJECT
public:
	explicit MainWindow(QWidget* parent = nullptr);
	~MainWindow() = default;

	void start();

signals:

public slots:

private:
	void initCommonParams();
	void initStatusBar();
	void initCentralWidget();
	void initConnections();

	void showDefaultTitle();
	void showLoadingStart();
	void showLoadingFinish();

private slots:
	void showMessage(const QString& text, int timeout = 5000);

private:
	Bike::WidgetMain* _bike;
	Books::WidgetMain* _books;
	Games::WidgetMain* _games;
	Trekking::WidgetMain* _trekking;

	QElapsedTimer _loading_timer;
};
