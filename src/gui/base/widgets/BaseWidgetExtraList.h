#pragma once

#include "BaseWidgetTree.h"

namespace Base
{

class ExtraList;

class WidgetExtraList : public WidgetTree
{
	Q_OBJECT
public:
	explicit WidgetExtraList(QWidget* parent = nullptr);
	~WidgetExtraList() = default;

	void update(const ExtraList& list);

signals:

private:
	void showByGroups(const ExtraList& list);

private:
	static const int WIDTH_TITLE = 0; // stretched
	static const int WIDTH_COUNT = 50;
	static const int WIDTH_NOTES = 400;
};

} // namespace Base
