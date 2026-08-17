#pragma once

#include <gui/base/widgets/BaseWidgetChart.h>

namespace Base
{
class ExtraList;
}

namespace Concerts
{

class DataList;

class WidgetChart : public Base::WidgetChart
{
	Q_OBJECT
public:
	explicit WidgetChart(QWidget* parent = nullptr);
	~WidgetChart() = default;

	void update(const DataList& data_list, const Base::ExtraList& extra_list);

signals:

private:
	void showByYears(const DataList& data_list);
	void showByArtists(const DataList& data_list, const Base::ExtraList& extra_list);
	void showByCountries(const DataList& data_list);
	void showByCities(const DataList& data_list);
	void showByPlaces(const DataList& data_list, const Base::ExtraList& extra_list);
};

} // namespace Concerts
