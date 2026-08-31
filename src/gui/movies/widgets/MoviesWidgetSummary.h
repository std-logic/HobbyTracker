#pragma once

#include <gui/base/widgets/BaseWidgetSummary.h>

class QLabel;

namespace Base
{
class ExtraList;
}

namespace Movies
{

class DataList;

class WidgetSummary : public Base::WidgetSummary
{
	Q_OBJECT
public:
	explicit WidgetSummary(QWidget* parent = nullptr);
	~WidgetSummary() = default;

	void update(const DataList& data_list, const Base::ExtraList& extra_list);

public slots:
	void setFavoritesOnly(Qt::CheckState state);

private:
	void initWidgets();

private:
	QLabel* _label_viewed_num = nullptr;
	QLabel* _label_movies_num = nullptr;
	QLabel* _label_series_num = nullptr;
	QLabel* _label_animation_num = nullptr;
	QLabel* _label_animation_series_num = nullptr;
	QLabel* _label_countries_num = nullptr;
	QLabel* _label_years = nullptr;
	QLabel* _label_rating = nullptr;

	bool _favorites_only = false;
};

} // namespace Movies
