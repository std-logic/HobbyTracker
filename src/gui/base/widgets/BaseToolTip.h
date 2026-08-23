#pragma once

#include <QLabel>

namespace Base
{

class ToolTip : public QLabel
{
	Q_OBJECT
public:
	explicit ToolTip(QWidget* parent = nullptr);
	virtual ~ToolTip() = default;

	void showText(const QString& text);

protected:
	void updatePos();
};

} // namespace Base
