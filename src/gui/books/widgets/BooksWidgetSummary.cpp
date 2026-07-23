#include "BooksWidgetSummary.h"
#include "../data/BooksDataList.h"

#include <common/Helper.h>

#include <QLabel>

Books::WidgetSummary::WidgetSummary(QWidget* parent)
	: Base::WidgetSummary{parent}
{
	initWidgets();
}

void Books::WidgetSummary::update(const DataList& data_list)
{
	if (data_list.empty()) {
		clear();
		return;
	}

	auto summary = data_list.summary();

	_label_authors_num->setText(QString::number(summary.authors_num));
	_label_books_num->setText(QString::number(summary.books_num));
	_label_genres_num->setText(QString::number(summary.genres_num));
	_label_years->setText(Helper::yearString(summary.min_year, summary.max_year));
	_label_rating->setText(QString::number(summary.rating, 'f', 1));
}

void Books::WidgetSummary::initWidgets()
{
	addWidget(tr("Авторов:"), _label_authors_num);
	addWidget(tr("Произведений:"), _label_books_num);
	addWidget(tr("Жанров:"), _label_genres_num);
	addWidget(tr("Годы:"), _label_years);
	addWidget(tr("Средняя оценка:"), _label_rating);

	addStretch();
}
