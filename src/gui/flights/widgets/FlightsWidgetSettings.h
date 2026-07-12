#pragma once

#include "../data/FlightsSettings.h"

#include <gui/base/widgets/BaseWidgetCsvSettings.h>
#include <gui/base/widgets/BaseWidgetSettings.h>

namespace Flights
{

class WidgetSettings : public Base::WidgetSettings
{
	Q_OBJECT
public:
	explicit WidgetSettings(const Settings& settings, QWidget* parent = nullptr);
	~WidgetSettings() = default;

signals:
	void readCsvData(const Csv::Settings& csv_settings);
	void saveSettings(const Settings& settings);

private:
	void initWidgets();

	void copyGuiToSettings();

private slots:
	void save() override;

private:
	Base::WidgetCsvSettings* _widget_csv_settings = nullptr;

	Settings _settings;
};

} // namespace Flights
