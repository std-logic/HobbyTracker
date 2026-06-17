#pragma once

#include <QPushButton>

namespace Base
{

class ButtonShow : public QPushButton
{
	Q_OBJECT
public:
	explicit ButtonShow(const QString& text, QWidget* parent = nullptr);
	virtual ~ButtonShow() = default;

signals:

};

} // namespace Base
