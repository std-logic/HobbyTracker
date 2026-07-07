#pragma once

#include <gui/base/widgets/BaseWidgetSummary.h>

class QLabel;

namespace Bike
{

class DataList;

class WidgetSummary : public Base::WidgetSummary
{
	Q_OBJECT
public:
	explicit WidgetSummary(QWidget* parent = nullptr);
	~WidgetSummary() = default;

	void update(const DataList& list);

signals:

private:
	void initWidgets();

private:
	QLabel* _label_years = nullptr;
	QLabel* _label_total_dist = nullptr;
	QLabel* _label_avg_dist = nullptr;
	QLabel* _label_total_time = nullptr;
	QLabel* _label_avg_time = nullptr;
};

} // namespace Bike
