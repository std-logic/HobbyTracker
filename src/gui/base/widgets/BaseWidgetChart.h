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

	void updateBars(const std::map<QString, uint32_t>& values);
	void updateBars(const std::map<uint32_t, uint32_t>& values);
	void updateBars(const std::map<uint32_t, std::pair<QString, uint32_t>>& values);
	void updateAxisYRange(uint32_t max_y);

private:
	uint32_t calcStepY(uint32_t max_y);

protected:
	int _view_mode = 0;
};

} // namespace Base
