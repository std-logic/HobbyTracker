#pragma once

#include <gui/base/widgets/BaseWidgetSummary.h>

class QLabel;

namespace Trekking
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
	QLabel* _label_tracks_num = nullptr;
	QLabel* _label_total_time = nullptr;
	QLabel* _label_total_dist = nullptr;
	QLabel* _label_highest_peak = nullptr;
};

} // namespace Trekking
