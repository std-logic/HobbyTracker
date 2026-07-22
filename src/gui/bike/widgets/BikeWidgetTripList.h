#pragma once

#include <gui/base/widgets/BaseWidgetTree.h>

namespace Bike
{

class TripList;

class WidgetTripList : public Base::WidgetTree
{
	Q_OBJECT
public:
	explicit WidgetTripList(QWidget* parent = nullptr);
	~WidgetTripList() = default;

	void update(const TripList& trip_list);

signals:

private:
	void showSimple(const TripList& trip_list);

private:
	static const int WIDTH_DATE = 180;
	static const int WIDTH_TIME = 100;
	static const int WIDTH_DIST = 100;
	static const int WIDTH_COUNTRIES = 200;
	static const int WIDTH_PLACES = 0; // stretched
};

} // namespace Bike
