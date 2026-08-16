#pragma once

#include <gui/base/widgets/BaseWidgetChart.h>

namespace Base
{
class ExtraList;
}

namespace Coins
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
	void showByCountries(const DataList& data_list, const Base::ExtraList& extra_list);
	void showByDecades(const DataList& data_list);
	void showByCenturies(const DataList& data_list);
	void showByDiameters(const DataList& data_list);
};

} // namespace Coins
