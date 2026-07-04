#pragma once

#include <QWidget>

class QHBoxLayout;
class QLabel;

namespace Base
{

class WidgetSummary : public QWidget
{
	Q_OBJECT
public:
	explicit WidgetSummary(QWidget* parent = nullptr);
	virtual ~WidgetSummary() = default;

signals:

protected:
	void addWidget(QLabel* widget);
	void addWidget(const QString& label_text, QLabel* widget);
	void addStretch(int stretch = 0);
	void addSpacing(int size = 30);

private:
	QHBoxLayout* _layout_main = nullptr;
};

} // namespace Base
