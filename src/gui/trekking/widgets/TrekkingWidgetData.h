#pragma once

#include "../data/TrekkingDataList.h"

#include <gui/base/widgets/BaseWidgetData.h>

class QLineEdit;

namespace Base
{
class ComboEdit;
}

namespace Trekking
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
	QLineEdit* _edit_date_start = nullptr;
	QLineEdit* _edit_date_end = nullptr;
	QLineEdit* _edit_time = nullptr;
	QLineEdit* _edit_dist = nullptr;
	QLineEdit* _edit_peak = nullptr;
	Base::ComboEdit* _combo_kind = nullptr;
	QLineEdit* _edit_countries = nullptr;
	QLineEdit* _edit_places = nullptr;

	DataList _data_list;
	Data _data;
};

} // namespace Trekking
