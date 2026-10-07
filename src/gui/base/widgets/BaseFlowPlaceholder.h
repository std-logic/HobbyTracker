#pragma once

#include <QFrame>

namespace Base
{

class FlowPlaceholder : public QFrame
{
public:
	explicit FlowPlaceholder(const QSize& size, QWidget* parent = nullptr);
	virtual ~FlowPlaceholder() = default;
};

} // namespace Base
