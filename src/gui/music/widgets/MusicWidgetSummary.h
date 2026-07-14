#pragma once

#include <gui/base/widgets/BaseWidgetSummary.h>

class QLabel;

namespace Music
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
	QLabel* _label_artists_num = nullptr;
	QLabel* _label_actives_num = nullptr;
	QLabel* _label_genres_num = nullptr;
	QLabel* _label_countries_num = nullptr;
	QLabel* _label_years = nullptr;
};

} // namespace Music
