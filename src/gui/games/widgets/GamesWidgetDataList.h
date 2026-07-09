#pragma once

#include <gui/base/widgets/BaseWidgetTree.h>

namespace Games
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
	void showBySeries(const DataList& data_list);
	void showByDevelopers(const DataList& data_list);
	void showByGenres(const DataList& data_list);
	void showByYears(const DataList& data_list);
	void showByDecades(const DataList& data_list);
	void showByRatings(const DataList& data_list);
	void showSimple(const DataList& data_list);

private:
	static const int WIDTH_TITLE = 0; // stretched
	static const int WIDTH_COUNT = 50;
	static const int WIDTH_DEVELOPER = 200;
	static const int WIDTH_GENRE = 130;
	static const int WIDTH_YEAR = 90;
	static const int WIDTH_RATING = 70;
};

} // namespace Games
