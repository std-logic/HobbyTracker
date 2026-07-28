#pragma once

#include "../data/BaseExtraList.h"
#include "BaseWidgetData.h"

#include <map>

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
	explicit WidgetExtra(size_t index, const ExtraList& data_list, QWidget* parent = nullptr);
	~WidgetExtra() = default;

	void addSpecialGroup(const QString& group, const QString& title_tip, const QString& notes_tip);

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
	void groupChanged(const QString& group);

private:
	Base::ComboEdit* _combo_group = nullptr;
	QLineEdit* _edit_title = nullptr;
	QLineEdit* _edit_notes = nullptr;

	ExtraList _data_list;
	Extra _data;

	std::map<QString, std::pair<QString, QString>> _special_groups;
};

} // namespace Base
