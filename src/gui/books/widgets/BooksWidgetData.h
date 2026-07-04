#pragma once

#include "../data/BooksDataList.h"

#include <gui/base/widgets/BaseWidgetData.h>

class QLineEdit;

namespace Base
{
class ComboEdit;
class WidgetRating;
}

namespace Books
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
	void authorTrChanged(int index);

private:
	Base::ComboEdit* _combo_author_tr = nullptr;
	Base::ComboEdit* _combo_author_orig = nullptr;
	QLineEdit* _edit_title_tr = nullptr;
	QLineEdit* _edit_title_orig = nullptr;
	Base::ComboEdit* _combo_genre = nullptr;
	QLineEdit* _edit_year = nullptr;
	Base::WidgetRating* _widget_rating = nullptr;

	size_t _index = 0;
	DataList _data_list;
	Data _data;
};

} // namespace Books
