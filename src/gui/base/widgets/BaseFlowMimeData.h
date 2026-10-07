#pragma once

#include <QMimeData>
#include <QPointer>

namespace Base
{

class FlowItem;

class FlowMimeData : public QMimeData
{
public:
	QPointer<FlowItem> widget;
};

} // namespace Base
