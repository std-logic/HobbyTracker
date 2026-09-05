#include "BaseWidgetChart.h"
#include "BaseToolTip.h"

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
	connect(bar_set, &QBarSet::hovered, this, &WidgetChart::barSetHovered);

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

	_tooltip = new ToolTip(this);

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

void Base::WidgetChart::setToolTipInsteadOfLabels(bool on)
{
	_tooltip_on = on;
	getAxisX()->setLabelsVisible(!on);
}

void Base::WidgetChart::updateBars(const std::map<QString, int>& values)
{
	QStringList array_x;
	QList<qreal> array_y;
	int min_y = std::numeric_limits<int>::max();
	int max_y = std::numeric_limits<int>::min();
	for (const auto& [val_x, val_y] : values) {
		array_x << val_x;
		array_y << val_y;
		if (min_y > val_y) { min_y = val_y; }
		if (max_y < val_y) { max_y = val_y; }
	}
	updateBars(array_x, array_y);
	updateAxisYRange(min_y, max_y);
}

void Base::WidgetChart::updateBars(const std::map<uint32_t, int>& values)
{
	QStringList array_x;
	QList<qreal> array_y;
	int min_y = std::numeric_limits<int>::max();
	int max_y = std::numeric_limits<int>::min();
	for (const auto& [val_x, val_y] : values) {
		array_x << QString::number(val_x);
		array_y << val_y;
		if (min_y > val_y) { min_y = val_y; }
		if (max_y < val_y) { max_y = val_y; }
	}
	updateBars(array_x, array_y);
	updateAxisYRange(min_y, max_y);
}

void Base::WidgetChart::updateBars(const std::map<uint32_t, std::pair<QString, int>>& values)
{
	QStringList array_x;
	QList<qreal> array_y;
	int min_y = std::numeric_limits<int>::max();
	int max_y = std::numeric_limits<int>::min();
	for (const auto& [_, val_xy] : values) {
		array_x << val_xy.first;
		array_y << val_xy.second;
		if (min_y > val_xy.second) { min_y = val_xy.second; }
		if (max_y < val_xy.second) { max_y = val_xy.second; }
	}
	updateBars(array_x, array_y);
	updateAxisYRange(min_y, max_y);
}

void Base::WidgetChart::updateBars(const std::vector<std::pair<QString, int>>& values)
{
	QStringList array_x;
	QList<qreal> array_y;
	int min_y = std::numeric_limits<int>::max();
	int max_y = std::numeric_limits<int>::min();
	for (const auto& [val_x, val_y] : values) {
		array_x << val_x;
		array_y << val_y;
		if (min_y > val_y) { min_y = val_y; }
		if (max_y < val_y) { max_y = val_y; }
	}
	updateBars(array_x, array_y);
	updateAxisYRange(min_y, max_y);
}

void Base::WidgetChart::updateBars(const QStringList& array_x, const QList<qreal>& array_y)
{
	getAxisX()->append(array_x);
	getBarSet()->append(array_y);
}

void Base::WidgetChart::updateAxisYRange(int min_y, int max_y)
{
	min_y = std::min(0, min_y);
	int step_y = calcStepY(max_y - min_y);
	int add = ((static_cast<double>(max_y % step_y) / step_y) > 0.55) ? 1 : 0;
	int range_start = (min_y < 0) ? ((min_y / step_y) - 1) * step_y : 0;
	int range_end = ((max_y / step_y) + 1 + add) * step_y;

	auto bar_axis_y = getAxisY();
	bar_axis_y->setRange(range_start, range_end);
	bar_axis_y->setTickCount(((range_end - range_start) / step_y) + 1);
}

int Base::WidgetChart::calcStepY(int range)
{
	return	(range > 60000)	? 20000 :	// 4+ steps
			(range > 30000)	? 10000 :	// 4-7 steps
			(range > 12000)	? 5000 :	// 3-7 steps
			(range > 6000)	? 2000 :	// 4-7 steps
			(range > 3000)	? 1000 :	// 4-7 steps
			(range > 1200)	? 500 :		// 3-7 steps
			(range > 600)	? 200 :		// 4-7 steps
			(range > 300)	? 100 :		// 4-7 steps
			(range > 120)	? 50 :		// 3-7 steps
			(range > 60)	? 20 :		// 4-7 steps
			(range > 30)	? 10 :		// 4-7 steps
			(range > 12)	? 5 :		// 3-7 steps
			(range > 5)		? 2 :		// 3-7 steps
							  1;		// 1-6 steps
}

void Base::WidgetChart::barSetHovered(bool status, int index)
{
	if (!_tooltip_on) { return; }
	if (status) {
		_tooltip->showText(QStringLiteral("%1: %2")
						   .arg(getAxisX()->at(index))
						   .arg(static_cast<int>(getBarSet()->at(index))));
	} else {
		_tooltip->hideText();
	}
}
