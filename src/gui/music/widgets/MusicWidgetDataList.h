#pragma once

#include <gui/base/widgets/BaseWidgetTree.h>

namespace Music
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
	void showSimple(const DataList& data_list);
	void showByGenres(const DataList& data_list);
	void showByCountries(const DataList& data_list);
	void showByDecades(const DataList& data_list);
	void showByStates(const DataList& data_list);

private:
	static const int WIDTH_TITLE = 0; // stretched
	static const int WIDTH_COUNT = 50;
	static const int WIDTH_GENRE = 200;
	static const int WIDTH_COUNTRY = 200;
	static const int WIDTH_YEAR = 130;
	static const int WIDTH_STATE = 70;
};

} // namespace Music
