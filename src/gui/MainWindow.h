#pragma once

#include <QMainWindow>

namespace Csv
{
class Data;
class Settings;
}

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
	void dataCsv(const Csv::Settings& csv_settings, const Csv::Data& csv_data);

signals:
	void readCsv(const Csv::Settings& csv_settings);

private:
	void initCommonParams();
	void initStatusBar();
	void initCentralWidget();
	void initConnections();

	void showDefaultTitle();

private:
	Books::WidgetMain* _books;
	Games::WidgetMain* _games;
};
