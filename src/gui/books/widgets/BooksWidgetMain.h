#pragma once

#include "../data/BooksDataList.h"
#include "../data/BooksSettings.h"

#include <storage/csv/CsvData.h>
#include <gui/base/widgets/BaseWidgetMain.h>

#include <QPointer>

namespace Books
{

class WidgetControl;
class WidgetSummary;
class WidgetList;
class WidgetStatistics;
class WidgetSettings;

class WidgetMain : public Base::WidgetMain
{
	Q_OBJECT
public:
	explicit WidgetMain(QWidget* parent = nullptr);
	~WidgetMain() = default;

	static QString getName() { return tr("Литература"); };

	void start() override;

signals:

private:
	void initWidgets();
	void initConnections();

private slots:
	void showSettings();
	void saveSettings(const Settings& settings);
	void readCsvData(const Csv::Settings& csv_settings);
	void updateList();

private:
	WidgetControl* _widget_control = nullptr;
	WidgetSummary* _widget_summary = nullptr;
	WidgetList* _widget_list = nullptr;
	WidgetStatistics* _widget_statistics = nullptr;
	QPointer<WidgetSettings> _widget_settings;

	std::optional<Csv::Data> _csv_data;
	std::optional<DataList> _data_list;
	Settings _settings;
};

} // namespace Books
