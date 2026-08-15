#pragma once

#include <QChartView>

class QBarSet;
class QValueAxis;
class QBarCategoryAxis;

namespace Base
{

class WidgetChart : public QChartView
{
	Q_OBJECT
public:
	explicit WidgetChart(QWidget* parent = nullptr);
	virtual ~WidgetChart() = default;

public slots:
	virtual void setViewMode(int view_mode);
	virtual void clearChart();

signals:
	void needUpdate();

protected:
	QBarSet* getBarSet();
	QValueAxis* getAxisY();
	QBarCategoryAxis* getAxisX();

	void updateBars(const std::map<QString, int>& values);
	void updateBars(const std::map<uint32_t, int>& values);
	void updateBars(const std::map<uint32_t, std::pair<QString, int>>& values);
	void updateBars(const std::vector<std::pair<QString, int>>& values);
	void updateAxisYRange(int min_y, int max_y);

private:
	int calcStepY(int range);

protected:
	int _view_mode = 0;
};

} // namespace Base
