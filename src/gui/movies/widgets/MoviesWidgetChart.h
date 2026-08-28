#pragma once

#include <gui/base/widgets/BaseWidgetChart.h>

namespace Base
{
class ExtraList;
}

namespace Movies
{

class DataList;

class WidgetChart : public Base::WidgetChart
{
	Q_OBJECT
public:
	explicit WidgetChart(QWidget* parent = nullptr);
	~WidgetChart() = default;

	void update(const DataList& data_list, const Base::ExtraList& extra_list);

public slots:
	void setFavoritesOnly(Qt::CheckState state);

signals:

private:
	void showByViewDates(const DataList& data_list);
	void showByGenres(const DataList& data_list);
	void showByCountries(const DataList& data_list, const Base::ExtraList& extra_list);
	void showByYears(const DataList& data_list);
	void showByDecades(const DataList& data_list);
	void showByDirectors(const DataList& data_list);
	void showByWriters(const DataList& data_list);
	void showByActors(const DataList& data_list);
	void showByRatings(const DataList& data_list);

private:
	bool _favorites_only = false;
};

} // namespace Movies
