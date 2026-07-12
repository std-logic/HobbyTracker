#pragma once

#include <gui/base/widgets/BaseWidgetTree.h>

namespace Flights
{

class DataList;

class WidgetDataList : public Base::WidgetTree
{
	Q_OBJECT
public:
	explicit WidgetDataList(QWidget* parent = nullptr);
	~WidgetDataList() = default;

	void update(const DataList& data_list);

signals:

private:
	void showByYears(const DataList& data_list);
	void showByCountries(const DataList& data_list);
	void showByCities(const DataList& data_list);
	void showByAirports(const DataList& data_list);
	void showSimple(const DataList& data_list);

private:
	static const int WIDTH_DATE = 280;
	static const int WIDTH_COUNT = 50;
	static const int WIDTH_POINTS = 0; // stretched
};

} // namespace Flights
