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

	void update(const DataList& list);

signals:

private:
	void showSimple(const DataList& list);

private:
	static const int WIDTH_YEAR = 200;
	static const int WIDTH_DIST = 200;
	static const int WIDTH_TIME = 200;
};

} // namespace Bike
