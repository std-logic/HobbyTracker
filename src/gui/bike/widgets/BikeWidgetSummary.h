#pragma once

#include <gui/base/widgets/BaseWidgetSummary.h>

class QLabel;

namespace Bike
{

class DataList;
class TripList;

class WidgetSummary : public Base::WidgetSummary
{
	Q_OBJECT
public:
	explicit WidgetSummary(QWidget* parent = nullptr);
	~WidgetSummary() = default;

	void update(const DataList& data_list, const TripList& trip_list);

signals:

private:
	void initWidgets();

private:
	QLabel* _label_years = nullptr;
	QLabel* _label_total_time = nullptr;
	QLabel* _label_total_dist = nullptr;

	QLabel* _label_trips_num = nullptr;
	QLabel* _label_trips_total_time = nullptr;
	QLabel* _label_trips_total_dist = nullptr;
};

} // namespace Bike
