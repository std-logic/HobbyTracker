#pragma once

#include <QPushButton>

namespace Base
{

class ButtonSettings : public QPushButton
{
	Q_OBJECT
public:
	explicit ButtonSettings(QWidget* parent = nullptr);
	virtual ~ButtonSettings() = default;

signals:

};

} // namespace Base
