#pragma once

#include "../data/MoviesDataList.h"

#include <gui/base/widgets/BaseWidgetData.h>

class QLineEdit;
class QCheckBox;

namespace Base
{
class ComboEdit;
class WidgetRating;
}

namespace Movies
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
	QLineEdit* _edit_title_tr = nullptr;
	QLineEdit* _edit_title_orig = nullptr;
	Base::ComboEdit* _combo_kind = nullptr;
	QLineEdit* _edit_genres = nullptr;
	QLineEdit* _edit_countries = nullptr;
	QLineEdit* _edit_directors = nullptr;
	QLineEdit* _edit_writers = nullptr;
	QLineEdit* _edit_actors = nullptr;
	QLineEdit* _edit_time = nullptr;
	QLineEdit* _edit_year = nullptr;
	Base::WidgetRating* _widget_rating = nullptr;
	QLineEdit* _edit_view_date = nullptr;
	QCheckBox* _check_favorite = nullptr;

	DataList _data_list;
	Data _data;
};

} // namespace Movies
