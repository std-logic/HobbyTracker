#pragma once

#include <QPushButton>

namespace Base
{

class ButtonSave : public QPushButton
{
	Q_OBJECT
public:
	explicit ButtonSave(QWidget* parent = nullptr);
	virtual ~ButtonSave() = default;

signals:

};

} // namespace Base
