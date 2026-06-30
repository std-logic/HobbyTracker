#pragma once

#include <gui/base/widgets/BaseWidgetChart.h>

namespace Books
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
	void showByDecades(const DataList& list);
	void showByCenturies(const DataList& list);
	void showByRatings(const DataList& list);
};

} // namespace Books
