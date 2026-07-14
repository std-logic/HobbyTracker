#pragma once

#include "../data/MusicDataList.h"
#include "../data/MusicSettings.h"

#include <gui/base/data/BaseExtraList.h>
#include <gui/base/widgets/BaseWidgetMain.h>

#include <QPointer>

namespace Base
{
class WidgetExtra;
class WidgetExtraList;
}

namespace Music
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

	static QString getName() { return tr("Музыка"); };

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

	void addExtra();
	void editExtra(const QString& id);
	void showExtra(size_t index);
	void saveExtra(size_t index, const Base::Extra& extra);
	void deleteExtra(const QString& id);

	void updateAll();
	void updateDependentOnData();
	void updateSummary();
	void updateDataList();
	void updateExtraList();
	void updateChart();

private:
	WidgetControl* _widget_control = nullptr;
	WidgetSummary* _widget_summary = nullptr;
	WidgetDataList* _widget_data_list = nullptr;
	Base::WidgetExtraList* _widget_extra_list = nullptr;
	WidgetChart* _widget_chart = nullptr;
	QPointer<WidgetSettings> _widget_settings;
	QPointer<WidgetData> _widget_data;
	QPointer<Base::WidgetExtra> _widget_extra;

	DataList _data_list;
	Base::ExtraList _extra_list;
	Settings _settings;
};

} // namespace Music
