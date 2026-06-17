#pragma once

#include <QWidget>

class QHBoxLayout;

namespace Base
{

class WidgetControl : public QWidget
{
	Q_OBJECT
public:
	explicit WidgetControl(QWidget* parent = nullptr);
	virtual ~WidgetControl() = default;

	virtual void start() = 0;

	void addWidget(QWidget* widget, int stretch = 0, Qt::Alignment alignment = Qt::Alignment());
	void addStretch(int stretch = 0);
	void addSpacing(int size = 20);

signals:

private:
	QHBoxLayout* _main_layout = nullptr;
};

} // namespace Base
