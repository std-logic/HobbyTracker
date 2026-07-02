#pragma once

#include <QPushButton>

namespace Base
{

class ButtonAdd : public QPushButton
{
	Q_OBJECT
public:
	explicit ButtonAdd(QWidget* parent = nullptr);
	virtual ~ButtonAdd() = default;

signals:

};

} // namespace Base
