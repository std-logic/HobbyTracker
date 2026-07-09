#pragma once

#include "../data/BikeDataList.h"

#include <gui/base/widgets/BaseWidgetData.h>

class QLineEdit;

namespace Bike
{

class WidgetData : public Base::WidgetData
{
	Q_OBJECT
public:
	explicit WidgetData(size_t index, const DataList& list, QWidget* parent = nullptr);
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
	QLineEdit* _edit_year = nullptr;
	QLineEdit* _edit_dist = nullptr;
	QLineEdit* _edit_time = nullptr;

	DataList _data_list;
	Data _data;
};

} // namespace Bike
