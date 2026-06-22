#pragma once

#include <QPushButton>

namespace Base
{

class ButtonCollapse : public QPushButton
{
	Q_OBJECT
public:
	explicit ButtonCollapse(QWidget* parent = nullptr);
	virtual ~ButtonCollapse() = default;

signals:

};

} // namespace Base
