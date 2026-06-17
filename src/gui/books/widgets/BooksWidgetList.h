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
};

} // namespace Books
