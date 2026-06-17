#pragma once

#include <QWidget>

class QVBoxLayout;

namespace Base
{

class WidgetMain : public QWidget
{
	Q_OBJECT
public:
	explicit WidgetMain(QWidget* parent = nullptr);
	virtual ~WidgetMain() = default;

	virtual void start() = 0;

	void addWidget(QWidget* widget, int stretch = 0, Qt::Alignment alignment = Qt::Alignment());
	void addStretch(int stretch = 0);

signals:

private:
	QVBoxLayout* _main_layout = nullptr;
};

} // namespace Base
