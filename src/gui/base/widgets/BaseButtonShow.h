#pragma once

#include <QPushButton>

#include <vector>

namespace Base
{

class ButtonShow : public QPushButton
{
	Q_OBJECT
public:
	explicit ButtonShow(const QString& text, QWidget* parent = nullptr);
	virtual ~ButtonShow() = default;

	void addSlaveWidgets(const std::vector<QWidget*>& widgets);

signals:

};

} // namespace Base
