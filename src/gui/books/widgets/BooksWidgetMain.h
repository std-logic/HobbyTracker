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
class WidgetChart;
class WidgetSettings;
class WidgetData;

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

	void addData();
	void editData(const QString& id);
	void showData(std::size_t index);
	void saveData(std::size_t index, const Data& data);

	void updateAll();
	void updateSummary();
	void updateList();
	void updateChart();

private:
	WidgetControl* _widget_control = nullptr;
	WidgetSummary* _widget_summary = nullptr;
	WidgetList* _widget_list = nullptr;
	WidgetChart* _widget_chart = nullptr;
	QPointer<WidgetSettings> _widget_settings;
	QPointer<WidgetData> _widget_data;

	std::optional<Csv::Data> _csv_data;
	std::optional<DataList> _data_list;
	Settings _settings;
};

} // namespace Books
