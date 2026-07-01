#include "BooksWidgetSummary.h"
#include "../data/BooksDataList.h"

#include <common/Helper.h>

#include <QLabel>

Books::WidgetSummary::WidgetSummary(QWidget* parent)
	: Base::WidgetSummary{parent}
{
	initWidgets();
}

void Books::WidgetSummary::update(const DataList& list)
{
	auto summary = list.summary();

	_label_authors_num->setText(QString::number(summary.authors_num));

	_label_books_num->setText(QString::number(summary.books_num));

	_label_genres_num->setText(QString::number(summary.genres_num));

	_label_years->setText(Helper::yearString(summary.min_year, summary.max_year));

	_label_rating->setText(QString::number(summary.rating, 'f', 1));
}

void Books::WidgetSummary::initWidgets()
{
	addWidget(tr("Авторов:"), _label_authors_num = new QLabel(this));

	addWidget(tr("Произведений:"), _label_books_num = new QLabel(this));

	addWidget(tr("Жанров:"), _label_genres_num = new QLabel(this));

	addWidget(tr("Годы:"), _label_years = new QLabel(this));

	addWidget(tr("Средняя оценка:"), _label_rating = new QLabel(this));

	addStretch();
}
