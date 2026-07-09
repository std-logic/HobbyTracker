#pragma once

#include "../data/TrekkingDataList.h"
#include "../data/TrekkingSettings.h"

#include <gui/base/widgets/BaseWidgetMain.h>

#include <QPointer>

namespace Trekking
{

class WidgetControl;
class WidgetSummary;
class WidgetData;
class WidgetDataList;
class WidgetChart;
class WidgetSettings;

class WidgetMain : public Base::WidgetMain
{
	Q_OBJECT
public:
	explicit WidgetMain(QWidget* parent = nullptr);
	~WidgetMain() = default;

	static QString getName() { return tr("Треккинг"); };

	void start() override;

private:
	void initWidgets();
	void initConnections();

private slots:
	void showSettings();
	void saveSettings(const Settings& settings);
	void readCsvData(const Csv::Settings& csv_settings);
	void saveCsvData();

	void addData();
	void editData(const QString& id);
	void showData(size_t index);
	void saveData(size_t index, const Data& data);
	void deleteData(const QString& id);

	void updateAll();
	void updateSummary();
	void updateDataList();
	void updateChart();

private:
	WidgetControl* _widget_control = nullptr;
	WidgetSummary* _widget_summary = nullptr;
	WidgetDataList* _widget_data_list = nullptr;
	WidgetChart* _widget_chart = nullptr;
	QPointer<WidgetSettings> _widget_settings;
	QPointer<WidgetData> _widget_data;

	DataList _data_list;
	Settings _settings;
};

} // namespace Trekking
