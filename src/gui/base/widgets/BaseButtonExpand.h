#pragma once

#include <QPushButton>

namespace Base
{

class ButtonExpand : public QPushButton
{
	Q_OBJECT
public:
	explicit ButtonExpand(QWidget* parent = nullptr);
	virtual ~ButtonExpand() = default;

signals:

};

} // namespace Base
