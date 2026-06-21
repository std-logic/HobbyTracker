#pragma once

#include "../data/BooksDataList.h"

#include <gui/base/widgets/BaseWidgetTree.h>

namespace Books
{

class WidgetList : public Base::WidgetTree
{
	Q_OBJECT
public:
	explicit WidgetList(QWidget* parent = nullptr);
	~WidgetList() = default;

	void showList(const DataList& list);

signals:

private:
	void showByAuthors(const DataList& list);
	void showByTitles(const DataList& list);
	void showByGenres(const DataList& list);
	void showByYears(const DataList& list);
	void showByRatings(const DataList& list);

private:
	static const int WIDTH_TITLE = 0; // stretched
	static const int WIDTH_COUNT = 50;
	static const int WIDTH_GENRE = 170;
	static const int WIDTH_YEAR = 90;
	static const int WIDTH_RATING = 80;
};

} // namespace Books
