#pragma once

#include <gui/base/widgets/BaseWidgetMain.h>

namespace Games
{

class WidgetMain : public Base::WidgetMain
{
	Q_OBJECT
public:
	explicit WidgetMain(QWidget* parent = nullptr);
	~WidgetMain() = default;

	static QString getName() { return tr("Игры"); };

	void start() override;

signals:

};

} // namespace Games
