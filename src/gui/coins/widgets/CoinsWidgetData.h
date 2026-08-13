#pragma once

#include "../data/CoinsDataList.h"

#include <gui/base/widgets/BaseWidgetData.h>

class QLineEdit;

namespace Base
{
class ComboEdit;
}

namespace Coins
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
	void countryChanged(const QString& country);
	void periodChanged(const QString& period);

private:
	Base::ComboEdit* _combo_country = nullptr;
	Base::ComboEdit* _combo_period = nullptr;
	Base::ComboEdit* _combo_currency = nullptr;
	Base::ComboEdit* _combo_value = nullptr;
	QLineEdit* _edit_title = nullptr;
	QLineEdit* _edit_diameter = nullptr;
	QLineEdit* _edit_number = nullptr;
	QLineEdit* _edit_year = nullptr;
	QLineEdit* _edit_version = nullptr;
	Base::ComboEdit* _combo_state = nullptr;

	DataList _data_list;
	Data _data;
};

} // namespace Coins
