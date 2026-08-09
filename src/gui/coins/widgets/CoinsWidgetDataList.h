#pragma once

#include <gui/base/widgets/BaseWidgetTree.h>

namespace Base
{
class ExtraList;
}

namespace Coins
{

class DataList;

class WidgetDataList : public Base::WidgetTree
{
	Q_OBJECT
public:
	explicit WidgetDataList(QWidget* parent = nullptr);
	~WidgetDataList() = default;

	void update(const DataList& data_list, const Base::ExtraList& extra_list);

signals:

private:
	void showByCountries(const DataList& data_list, const Base::ExtraList& extra_list);
	void showByDecades(const DataList& data_list);
	void showByCenturies(const DataList& data_list);
	void showSimple(const DataList& data_list);

private:
	static const int WIDTH_COUNT = 50;
	static const int WIDTH_COUNTRY_SMALL = 230;
	static const int WIDTH_COUNTRY_BIG = 350;
	static const int WIDTH_PERIOD = 230;
	static const int WIDTH_CURRENCY = 230;
	static const int WIDTH_VALUE = 150;
	static const int WIDTH_TITLE = 0; // stretched
	static const int WIDTH_DIAMETER = 55;
	static const int WIDTH_NUMBER = 100;
	static const int WIDTH_YEAR = 90;
	static const int WIDTH_VERSION = 50;
	static const int WIDTH_STATE = 50;
};

} // namespace Coins
