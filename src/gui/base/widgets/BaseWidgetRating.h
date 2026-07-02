#pragma once

#include <QWidget>

#include <array>

class QHBoxLayout;
class QPushButton;
class QButtonGroup;

namespace Base
{

class WidgetRating : public QWidget
{
	Q_OBJECT
public:
	explicit WidgetRating(QWidget* parent = nullptr);
	virtual ~WidgetRating() = default;

	void setRating(uint32_t rating);
	uint32_t rating() const;

signals:

private:
	void initWidgets();

private:
	QHBoxLayout* _layout_main = nullptr;
	QButtonGroup* _group_buttons = nullptr;
	std::array<QPushButton*, 10> _buttons;
};

} // namespace Base
