#pragma once

#include <gui/base/widgets/BaseWidgetChart.h>

namespace Movies
{

class DataList;

class WidgetChart : public Base::WidgetChart
{
	Q_OBJECT
public:
	explicit WidgetChart(QWidget* parent = nullptr);
	~WidgetChart() = default;

	void update(const DataList& data_list);

public slots:
	void setFavoritesOnly(Qt::CheckState state);

signals:

private:
	void showByViewDates(const DataList& data_list);
	void showByYears(const DataList& data_list);
	void showByDecades(const DataList& data_list);
	void showByRatings(const DataList& data_list);

private:
	bool _favorites_only = false;
};

} // namespace Movies
