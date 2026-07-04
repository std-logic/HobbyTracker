#include "BaseButtonShow.h"

Base::ButtonShow::ButtonShow(const QString& text, QWidget* parent)
	: QPushButton{text, parent}
{
	setCheckable(true);
}

void Base::ButtonShow::addSlaveWidgets(const std::vector<QWidget*>& widgets)
{
	for (auto widget : widgets) {
		widget->setEnabled(false);
	}

	connect(this, &ButtonShow::toggled, this, [widgets](bool on) {
		for (auto widget : widgets) {
			widget->setEnabled(on);
		}
	});
}
