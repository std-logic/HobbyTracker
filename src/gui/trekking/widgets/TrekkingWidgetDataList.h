#pragma once

#include <gui/base/widgets/BaseWidgetTree.h>

namespace Trekking
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
	void showByCountries(const DataList& data_list);
	void showByKinds(const DataList& data_list);

private:
	static const int WIDTH_DATE = 180;
	static const int WIDTH_COUNT = 50;
	static const int WIDTH_TIME = 100;
	static const int WIDTH_DIST = 100;
	static const int WIDTH_PEAK = 110;
	static const int WIDTH_KIND = 140;
	static const int WIDTH_COUNTRIES = 200;
	static const int WIDTH_PLACES = 0; // stretched
};

} // namespace Trekking
