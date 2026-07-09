#pragma once

#include "../data/BikeTripList.h"

#include <gui/base/widgets/BaseWidgetData.h>

class QLineEdit;

namespace Bike
{

class WidgetTrip : public Base::WidgetData
{
	Q_OBJECT
public:
	explicit WidgetTrip(size_t index, const TripList& list, QWidget* parent = nullptr);
	~WidgetTrip() = default;

signals:
	void saveData(size_t index, const Trip& data);

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
	QLineEdit* _edit_countries = nullptr;
	QLineEdit* _edit_places = nullptr;

	TripList _data_list;
	Trip _data;
};

} // namespace Bike
