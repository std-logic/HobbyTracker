#pragma once

#include <gui/base/widgets/BaseWidgetSummary.h>

class QLabel;

namespace Books
{

class DataList;

class WidgetSummary : public Base::WidgetSummary
{
	Q_OBJECT
public:
	explicit WidgetSummary(QWidget* parent = nullptr);
	~WidgetSummary() = default;

	void update(const DataList& data_list);

signals:

private:
	void initWidgets();

private:
	QLabel* _label_authors_num = nullptr;
	QLabel* _label_books_num = nullptr;
	QLabel* _label_genres_num = nullptr;
	QLabel* _label_years = nullptr;
	QLabel* _label_rating = nullptr;
};

} // namespace Books
