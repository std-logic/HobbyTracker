#pragma once

#include "../data/BaseExtraList.h"
#include "BaseWidgetData.h"

class QLineEdit;

namespace Base
{
class ComboEdit;
}

namespace Base
{

class WidgetExtra : public WidgetData
{
	Q_OBJECT
public:
	explicit WidgetExtra(size_t index, const ExtraList& list, QWidget* parent = nullptr);
	~WidgetExtra() = default;

signals:
	void saveExtra(size_t index, const Extra& data);

private:
	void initData();
	void initCommonParams();
	void initWidgets();

	void copyDataToGui();
	bool copyGuiToData();

private slots:
	void save() override;

private:
	Base::ComboEdit* _combo_group = nullptr;
	QLineEdit* _edit_title = nullptr;
	QLineEdit* _edit_notes = nullptr;

	ExtraList _data_list;
	Extra _data;
};

} // namespace Base
