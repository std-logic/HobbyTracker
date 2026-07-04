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

signals:
	void showMessage(const QString& text, int timeout = 5000);

protected:
	void addWidget(QWidget* widget, int stretch = 0, Qt::Alignment alignment = Qt::Alignment());
	void addStretch(int stretch = 0);

private:
	QVBoxLayout* _layout_main = nullptr;
};

} // namespace Base
