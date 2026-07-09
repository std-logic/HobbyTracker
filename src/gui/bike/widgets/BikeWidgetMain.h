#pragma once

#include "../data/BikeDataList.h"
#include "../data/BikeTripList.h"
#include "../data/BikeSettings.h"

#include <gui/base/widgets/BaseWidgetMain.h>

#include <QPointer>

namespace Bike
{

class WidgetControl;
class WidgetSummary;
class WidgetData;
class WidgetDataList;
class WidgetTrip;
class WidgetTripList;
class WidgetChart;
class WidgetSettings;

class WidgetMain : public Base::WidgetMain
{
	Q_OBJECT
public:
	explicit WidgetMain(QWidget* parent = nullptr);
	~WidgetMain() = default;

	static QString getName() { return tr("Велосипед"); };

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

	void addTrip();
	void editTrip(const QString& id);
	void showTrip(size_t index);
	void saveTrip(size_t index, const Trip& trip);
	void deleteTrip(const QString& id);

	void updateAll();
	void updateDependentOnData();
	void updateDependentOnTrip();
	void updateSummary();
	void updateDataList();
	void updateTripList();
	void updateChart();

private:
	WidgetControl* _widget_control = nullptr;
	WidgetSummary* _widget_summary = nullptr;
	WidgetDataList* _widget_data_list = nullptr;
	WidgetTripList* _widget_trip_list = nullptr;
	WidgetChart* _widget_chart = nullptr;
	QPointer<WidgetSettings> _widget_settings;
	QPointer<WidgetData> _widget_data;
	QPointer<WidgetTrip> _widget_trip;

	DataList _data_list;
	TripList _trip_list;
	Settings _settings;
};

} // namespace Bike
