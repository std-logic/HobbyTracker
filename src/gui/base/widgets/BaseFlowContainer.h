#pragma once

#include "BaseFlowMimeData.h"

#include <QWidget>

class QHBoxLayout;
class QPushButton;
class QDragEnterEvent;
class QDragLeaveEvent;
class QDragMoveEvent;
class QDropEvent;

namespace Base
{

class FlowLayout;
class FlowItem;
class FlowPlaceholder;

class FlowContainer : public QWidget
{
	Q_OBJECT
public:
	explicit FlowContainer(QWidget* parent = nullptr);
	virtual ~FlowContainer() = default;

	void setFixedItemWidth(int item_width) { _fixed_item_width = item_width; }

	int count() const;
	QWidget* widgetAt(int index) const;

public slots:
	void addWidget(FlowItem* widget);
	void delWidget(QWidget* widget);

signals:
	void addWidgetRequest();

protected:
	void dragEnterEvent(QDragEnterEvent* event) override;
	void dragMoveEvent(QDragMoveEvent* event) override;
	void dragLeaveEvent(QDragLeaveEvent* event) override;
	void dropEvent(QDropEvent* event) override;

private:
	void initCommonParams();
	void initWidgets();

	FlowItem* widgetFromMimeData(const QMimeData* mime_data) const;
	int indexFromPosition(const QPoint& position) const;
	void startDragging(FlowItem* widget);
	void movePlaceholder(const QPoint& position);
	void finishDragging();
	void scheduleHeightAdjustment();

private slots:
	void adjustWindowHeight();

private:
	QHBoxLayout* _layout_main = nullptr;
	QPushButton* _button_add = nullptr;
	FlowLayout* _layout_flow = nullptr;

	FlowItem* _dragged_widget = nullptr;
	FlowPlaceholder* _placeholder_widget = nullptr;
	int _placeholder_index = -1;

	bool _adjust_window_height_scheduled = false;
	int _fixed_item_width = 150;
};

} // namespace Base
