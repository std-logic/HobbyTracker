#pragma once

#include "../common/FlightsCommon.h"
#include "../data/FlightsDataList.h"

#include <gui/base/widgets/BaseWidgetData.h>

class QLineEdit;

namespace Base
{
class ComboEdit;
}

namespace Flights
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
	void countryChanged(size_t point, const QString& country);
	void cityChanged(size_t point, const QString& city);
	void airportChanged(size_t point, const QString& airport);

private:
	QLineEdit* _edit_date = nullptr;
	struct FlightPoint
	{
		Base::ComboEdit* combo_country = nullptr;
		Base::ComboEdit* combo_city = nullptr;
		Base::ComboEdit* combo_airport = nullptr;
		QLineEdit* edit_dist = nullptr;
	}	_widgets_point[max_points_num];

	DataList _data_list;
	Data _data;
	DataList::DistList _dist_list;
};

} // namespace Flights
