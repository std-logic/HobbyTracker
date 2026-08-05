#pragma once

#include <gui/base/widgets/BaseWidgetTree.h>

namespace Movies
{

class DataList;

class WidgetDataList : public Base::WidgetTree
{
	Q_OBJECT
public:
	explicit WidgetDataList(QWidget* parent = nullptr);
	~WidgetDataList() = default;

	void update(const DataList& data_list);

public slots:
	void setFavoritesOnly(Qt::CheckState state);

signals:

private:
	void showSimple(const DataList& data_list);
	void showByKinds(const DataList& data_list);
	void showByGenres(const DataList& data_list);
	void showByCountries(const DataList& data_list);
	void showByYears(const DataList& data_list);
	void showByDecades(const DataList& data_list);
	void showByDirectors(const DataList& data_list);
	void showByWriters(const DataList& data_list);
	void showByActors(const DataList& data_list);
	void showByRatings(const DataList& data_list);

private:
	static const int WIDTH_VIEW_DATE_SMALL = 130;
	static const int WIDTH_VIEW_DATE_MEDIUM = 170;
	static const int WIDTH_VIEW_DATE_BIG = 200;
	static const int WIDTH_TITLE = 0; // stretched
	static const int WIDTH_COUNT = 50;
	static const int WIDTH_GENRES = 140;
	static const int WIDTH_COUNTRIES = 140;
	static const int WIDTH_DIRECTORS = 150;
	static const int WIDTH_WRITERS = 150;
	static const int WIDTH_ACTORS = 0; // stretched
	static const int WIDTH_YEAR = 90;
	static const int WIDTH_RATING = 70;

	bool _favorites_only = false;
};

} // namespace Movies
