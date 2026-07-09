#pragma once

#include "../data/GamesDataList.h"

#include <gui/base/widgets/BaseWidgetData.h>

class QLineEdit;

namespace Base
{
class ComboEdit;
class WidgetRating;
}

namespace Games
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
	Base::ComboEdit* _combo_series = nullptr;
	QLineEdit* _edit_title = nullptr;
	Base::ComboEdit* _combo_developer = nullptr;
	Base::ComboEdit* _combo_genre = nullptr;
	QLineEdit* _edit_year = nullptr;
	Base::WidgetRating* _widget_rating = nullptr;

	DataList _data_list;
	Data _data;
};

} // namespace Games
