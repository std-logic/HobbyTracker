#pragma once

#include <QMainWindow>

#include <QElapsedTimer>

namespace Bike { class WidgetMain; }
namespace Books { class WidgetMain; }
namespace Coins { class WidgetMain; }
namespace Concerts { class WidgetMain; }
namespace Flights { class WidgetMain; }
namespace Games { class WidgetMain; }
namespace Movies { class WidgetMain; }
namespace Music { class WidgetMain; }
namespace Player { class WidgetMain; }
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
	Coins::WidgetMain* _coins;
	Concerts::WidgetMain* _concerts;
	Flights::WidgetMain* _flights;
	Games::WidgetMain* _games;
	Movies::WidgetMain* _movies;
	Music::WidgetMain* _music;
	Player::WidgetMain* _player;
	Trekking::WidgetMain* _trekking;

	QElapsedTimer _loading_timer;
};
