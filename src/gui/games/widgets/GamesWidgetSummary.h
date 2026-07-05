#pragma once

#include <gui/base/widgets/BaseWidgetSummary.h>

class QLabel;

namespace Games
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
	QLabel* _label_series_num = nullptr;
	QLabel* _label_games_num = nullptr;
	QLabel* _label_genres_num = nullptr;
	QLabel* _label_developers_num = nullptr;
	QLabel* _label_years = nullptr;
	QLabel* _label_rating = nullptr;
};

} // namespace Games
