#include "BaseWidgetChart.h"

#include <common/Global.h>

#include <QVBoxLayout>
#include <QBarSet>
#include <QBarSeries>
#include <QValueAxis>
#include <QBarCategoryAxis>

Base::WidgetChart::WidgetChart(QWidget* parent)
	: QChartView{parent}
{
	setViewportMargins(0, 0, 0, 0);
	setRubberBand(QChartView::NoRubberBand);
	setRenderHint(QPainter::Antialiasing);
	setFrameShape(QFrame::Box);

	auto bar_chart = chart();

	bar_chart->setTheme(QChart::ChartThemeDark);
	bar_chart->setBackgroundBrush(QColor(100, 100, 100));
	bar_chart->setMargins({3, 0, 10, 0});
	bar_chart->legend()->setVisible(false);
	auto title_font = bar_chart->titleFont();
	title_font.setPointSize(Global::Sizes::font_big);
	bar_chart->setTitleFont(title_font);

	auto bar_set = new QBarSet("");
	bar_set->setLabelColor(QColor(Qt::white));
	bar_set->setBorderColor(QColor(60, 120, 180));
	bar_set->setColor(QColor(90, 155, 215));
	auto label_font = bar_set->labelFont();
	label_font.setPointSize(Global::Sizes::font_small);
	bar_set->setLabelFont(label_font);

	auto bar_series = new QBarSeries();
	bar_series->setLabelsVisible(true);
	bar_series->setLabelsPosition(QAbstractBarSeries::LabelsOutsideEnd);
	bar_series->append(bar_set);
	bar_chart->addSeries(bar_series);

	auto bar_axis_x = new QBarCategoryAxis;
	bar_chart->addAxis(bar_axis_x, Qt::AlignBottom);
	bar_series->attachAxis(bar_axis_x);

	auto bar_axis_y = new QValueAxis;
	bar_axis_y->setLabelFormat("%d");
	bar_chart->addAxis(bar_axis_y, Qt::AlignLeft);
	bar_series->attachAxis(bar_axis_y);

	hide();
}

void Base::WidgetChart::setViewMode(int view_mode)
{
	if ((view_mode < 0) || (_view_mode == view_mode)) { return; }
	_view_mode = view_mode;
	emit needUpdate();
}

void Base::WidgetChart::clearChart()
{
	auto bar_axis_x = getAxisX();
	bar_axis_x->clear();

	auto bar_sets_1 = getBarSet();
	bar_sets_1->remove(0, bar_sets_1->count());

	chart()->setTitle(QString());
}

QBarSet* Base::WidgetChart::getBarSet()
{
	auto bar_chart = chart();
	auto bar_series = bar_chart->series();
	auto bar_series_1 = bar_series.first();
	auto bar_sets = reinterpret_cast<QAbstractBarSeries*>(bar_series_1)->barSets();
	auto bar_set_1 = bar_sets.first();
	return bar_set_1;
}

QValueAxis* Base::WidgetChart::getAxisY()
{
	auto bar_chart = chart();
	auto bar_axis_y = bar_chart->axes(Qt::Vertical);
	auto bar_axis_y_1 = reinterpret_cast<QValueAxis*>(bar_axis_y.first());
	return bar_axis_y_1;
}

QBarCategoryAxis* Base::WidgetChart::getAxisX()
{
	auto bar_chart = chart();
	auto bar_axis_x = bar_chart->axes(Qt::Horizontal);
	auto bar_axis_x_1 = reinterpret_cast<QBarCategoryAxis*>(bar_axis_x.first());
	return bar_axis_x_1;
}

void Base::WidgetChart::updateBars(const std::map<QString, uint32_t>& values)
{
	auto bar_axis_x = getAxisX();
	auto bar_set = getBarSet();
	uint32_t max_y = std::numeric_limits<uint32_t>::min();
	for (const auto& [val_x, val_y] : values) {
		bar_axis_x->append(val_x);
		bar_set->append(val_y);
		if (max_y < val_y) { max_y = val_y; }
	}
	updateAxisYRange(max_y);
}

void Base::WidgetChart::updateBars(const std::map<uint32_t, uint32_t>& values)
{
	auto bar_axis_x = getAxisX();
	auto bar_set = getBarSet();
	uint32_t max_y = std::numeric_limits<uint32_t>::min();
	for (const auto& [val_x, val_y] : values) {
		bar_axis_x->append(QString::number(val_x));
		bar_set->append(val_y);
		if (max_y < val_y) { max_y = val_y; }
	}
	updateAxisYRange(max_y);
}

void Base::WidgetChart::updateBars(const std::map<uint32_t, std::pair<QString, uint32_t>>& values)
{
	auto bar_axis_x = getAxisX();
	auto bar_set = getBarSet();
	uint32_t max_y = std::numeric_limits<uint32_t>::min();
	for (const auto& [_, val_xy] : values) {
		bar_axis_x->append(val_xy.first);
		bar_set->append(val_xy.second);
		if (max_y < val_xy.second) { max_y = val_xy.second; }
	}
	updateAxisYRange(max_y);
}

void Base::WidgetChart::updateAxisYRange(uint32_t max_y)
{
	auto step_y = calcStepY(max_y);

	auto bar_axis_y = getAxisY();
	bar_axis_y->setRange(0, ((max_y / step_y) + 1) * step_y);
	bar_axis_y->setTickCount((max_y / step_y) + 2);
}

uint32_t Base::WidgetChart::calcStepY(uint32_t max_y)
{
	return	(max_y > 60000)	? 20000 :	// 4+ steps
			(max_y > 30000)	? 10000 :	// 4-7 steps
			(max_y > 12000)	? 5000 :	// 3-7 steps
			(max_y > 6000)	? 2000 :	// 4-7 steps
			(max_y > 3000)	? 1000 :	// 4-7 steps
			(max_y > 1200)	? 500 :		// 3-7 steps
			(max_y > 600)	? 200 :		// 4-7 steps
			(max_y > 300)	? 100 :		// 4-7 steps
			(max_y > 120)	? 50 :		// 3-7 steps
			(max_y > 60)	? 20 :		// 4-7 steps
			(max_y > 30)	? 10 :		// 4-7 steps
			(max_y > 12)	? 5 :		// 3-7 steps
			(max_y > 5)		? 2 :		// 3-7 steps
							  1;		// 1-6 steps
}
