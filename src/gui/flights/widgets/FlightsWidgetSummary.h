#pragma once

#include <gui/base/widgets/BaseWidgetSummary.h>

class QLabel;

namespace Flights
{

class DataList;

class WidgetSummary : public Base::WidgetSummary
{
	Q_OBJECT
public:
	explicit WidgetSummary(QWidget* parent = nullptr);
	~WidgetSummary() = default;

	void update(const DataList& data_list);

private:
	void initWidgets();

private:
	QLabel* _label_years = nullptr;
	QLabel* _label_countries_num = nullptr;
	QLabel* _label_cities_num = nullptr;
	QLabel* _label_airports_num = nullptr;
	QLabel* _label_flights_num = nullptr;
	QLabel* _label_local_num = nullptr;
	QLabel* _label_international_num = nullptr;
	QLabel* _label_dist = nullptr;
};

} // namespace Flights
