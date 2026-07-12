#pragma once

#include <gui/base/widgets/BaseWidgetTree.h>

namespace Bike
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

private:
	static const int WIDTH_YEAR = 180;
	static const int WIDTH_TIME = 80;
	static const int WIDTH_DIST = 80;
};

} // namespace Bike
