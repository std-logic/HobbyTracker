#pragma once

#include <gui/base/widgets/BaseWidgetSummary.h>

class QLabel;

namespace Concerts
{

class DataList;

class WidgetSummary : public Base::WidgetSummary
{
	Q_OBJECT
public:
	explicit WidgetSummary(QWidget* parent = nullptr);
	~WidgetSummary() = default;

	void update(const DataList& data_list);

private:
	void initWidgets();

private:
	QLabel* _label_years = nullptr;
	QLabel* _label_countries_num = nullptr;
	QLabel* _label_cities_num = nullptr;
	QLabel* _label_places_num = nullptr;
	QLabel* _label_artists_num = nullptr;
	QLabel* _label_concerts_num = nullptr;
};

} // namespace Concerts
