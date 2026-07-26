#pragma once

#include "../data/ConcertsDataList.h"

#include <gui/base/widgets/BaseWidgetData.h>

class QLineEdit;

namespace Base
{
class ComboEdit;
}

namespace Concerts
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
	void cityChanged(const QString& city);

private:
	QLineEdit* _edit_date = nullptr;
	QLineEdit* _edit_artists = nullptr;
	Base::ComboEdit* _combo_description = nullptr;
	Base::ComboEdit* _combo_country = nullptr;
	Base::ComboEdit* _combo_city = nullptr;
	Base::ComboEdit* _combo_place = nullptr;

	DataList _data_list;
	Data _data;
};

} // namespace Concerts
