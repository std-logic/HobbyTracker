#include "CoinsWidgetSummary.h"
#include "../data/CoinsDataList.h"

#include <common/Helper.h>

#include <QLabel>

Coins::WidgetSummary::WidgetSummary(QWidget* parent)
	: Base::WidgetSummary{parent}
{
	initWidgets();
}

void Coins::WidgetSummary::update(const DataList& data_list)
{
	if (data_list.empty()) {
		clear();
		return;
	}

	auto summary = data_list.summary();

	_label_coins_num->setText(QString::number(summary.coins_num));
	_label_countries_num->setText(QString::number(summary.countries_num));
	_label_diameters->setText(QStringLiteral("%1-%2")
			.arg(summary.min_diameter*0.1, 0, 'f', 1)
			.arg(summary.max_diameter*0.1, 0, 'f', 1));
	_label_years->setText(Helper::yearString(summary.min_year, summary.max_year));
}

void Coins::WidgetSummary::initWidgets()
{
	addWidget(tr("Монет:"), _label_coins_num);
	addWidget(tr("Стран:"), _label_countries_num);
	addWidget(tr("Диаметры:"), _label_diameters);
	addWidget(tr("Годы:"), _label_years, 0);

	addStretch();
}
