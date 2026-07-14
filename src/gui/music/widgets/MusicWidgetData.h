#pragma once

#include "../data/MusicDataList.h"

#include <gui/base/widgets/BaseWidgetData.h>

class QLineEdit;
class QCheckBox;

namespace Base
{
class ComboEdit;
}

namespace Music
{

class WidgetData : public Base::WidgetData
{
	Q_OBJECT
public:
	explicit WidgetData(size_t index, const DataList& data_list, QWidget* parent = nullptr);
	~WidgetData() = default;

signals:
	void saveData(size_t index, const Data& data);

private:
	void initData();
	void initCommonParams();
	void initWidgets();

	void copyDataToGui();
	bool copyGuiToData();

private slots:
	void save() override;

private:
	QLineEdit* _edit_title = nullptr;
	Base::ComboEdit* _combo_genre = nullptr;
	Base::ComboEdit* _combo_country = nullptr;
	QLineEdit* _edit_year = nullptr;
	QCheckBox* _check_state = nullptr;

	DataList _data_list;
	Data _data;
};

} // namespace Music
