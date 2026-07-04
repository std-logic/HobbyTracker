#pragma once

#include <gui/base/widgets/BaseWidgetTree.h>

namespace Books
{

class DataList;

class WidgetDataList : public Base::WidgetTree
{
	Q_OBJECT
public:
	explicit WidgetDataList(QWidget* parent = nullptr);
	~WidgetDataList() = default;

	void update(const DataList& list);

signals:

private:
	void showByAuthors(const DataList& list);
	void showByGenres(const DataList& list);
	void showByDecades(const DataList& list);
	void showByCenturies(const DataList& list);
	void showByRatings(const DataList& list);
	void showSimple(const DataList& list);

private:
	static const int WIDTH_TITLE = 0; // stretched
	static const int WIDTH_COUNT = 50;
	static const int WIDTH_GENRE = 170;
	static const int WIDTH_YEAR = 90;
	static const int WIDTH_RATING = 80;
};

} // namespace Books
