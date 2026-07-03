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

public slots:
	void highlight(bool on);
};

} // namespace Base
