#pragma once

#include <gui/base/widgets/BaseWidgetChart.h>

namespace Games
{

class DataList;

class WidgetChart : public Base::WidgetChart
{
	Q_OBJECT
public:
	explicit WidgetChart(QWidget* parent = nullptr);
	~WidgetChart() = default;

	void update(const DataList& list);

signals:

private:
	void showByYears(const DataList& list);
	void showByDecades(const DataList& list);
	void showByRatings(const DataList& list);
};

} // namespace Games
