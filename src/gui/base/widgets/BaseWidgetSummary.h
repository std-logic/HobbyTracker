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

protected:
	void addWidget(QLabel*& widget, int spacing = 30);
	void addWidget(const QString& label_text, QLabel*& widget, int spacing = 30);
	void addStretch(int stretch = 0);
	void addSpacing(int size = 30);

private:
	QHBoxLayout* _layout_main = nullptr;
};

} // namespace Base
