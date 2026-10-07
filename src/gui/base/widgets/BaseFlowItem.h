#pragma once

#include <QFrame>
#include <QPoint>

class QHBoxLayout;
class QPushButton;
class QLabel;

namespace Base
{

class FlowItem : public QFrame
{
	Q_OBJECT
public:
	explicit FlowItem(QWidget* parent = nullptr);
	virtual ~FlowItem() = default;

	void addWidget(QWidget* widget);
	QWidget* widget() const;

signals:
	void delWidget(QWidget* widget);

protected:
	void mousePressEvent(QMouseEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;

private:
	void initCommonParams();
	void initWidgets();

	void disableChildDrops(QWidget* widget);

private:
	QHBoxLayout* _layout_main = nullptr;
	QLabel* _label_drag = nullptr;
	QPushButton* _button_del = nullptr;

	bool _drag_started = false;
	QPoint _drag_start_pos;
};

} // namespace Base
