#pragma once

#include <QChartView>

class QBarSet;
class QValueAxis;
class QBarCategoryAxis;

namespace Base
{

class ToolTip;

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

	void setToolTipInsteadOfLabels(bool on);

	void updateBars(const std::map<QString, int>& values);
	void updateBars(const std::map<uint32_t, int>& values);
	void updateBars(const std::map<uint32_t, std::pair<QString, int>>& values);
	void updateBars(const std::vector<std::pair<QString, int>>& values);

private:
	void updateBars(const QStringList& array_x, const QList<qreal>& array_y);
	void updateAxisYRange(int min_y, int max_y);
	int calcStepY(int range);

private slots:
	void barSetHovered(bool status, int index);

protected:
	int _view_mode = 0;

	Base::ToolTip* _tooltip = nullptr;
	bool _tooltip_on = false;
};

} // namespace Base
