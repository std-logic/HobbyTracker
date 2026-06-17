#pragma once

#include "../data/BooksDataList.h"

#include <gui/base/widgets/BaseWidgetMain.h>

namespace Books
{

class WidgetControl;
class WidgetList;
class WidgetStatistics;

class WidgetMain : public Base::WidgetMain
{
	Q_OBJECT
public:
	explicit WidgetMain(QWidget* parent = nullptr);
	~WidgetMain() = default;

	static QString getName() { return tr("Литература"); };

	void start() override;

signals:

private:
	void initGui();
	void initConnections();

private slots:
	void updateList();

private:
	WidgetControl* _control = nullptr;
	WidgetList* _list = nullptr;
	WidgetStatistics* _statistics = nullptr;

	std::optional<DataList> _data_list;
};

} // namespace Books
