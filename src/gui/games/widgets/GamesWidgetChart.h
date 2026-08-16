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

	void update(const DataList& data_list);

signals:

private:
	void showBySeries(const DataList& data_list);
	void showByDevelopers(const DataList& data_list);
	void showByGenres(const DataList& data_list);
	void showByYears(const DataList& data_list);
	void showByDecades(const DataList& data_list);
	void showByRatings(const DataList& data_list);
};

} // namespace Games
