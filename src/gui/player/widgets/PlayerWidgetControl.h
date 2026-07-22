#pragma once

#include "../common/PlayerCommon.h"

#include <gui/base/widgets/BaseWidgetControl.h>

namespace Base
{
class ButtonCollapse;
class ButtonExpand;
class ButtonShow;
class ComboBox;
}

class QPushButton;

namespace Player
{

class WidgetControl : public Base::WidgetControl
{
	Q_OBJECT
public:
	explicit WidgetControl(QWidget* parent = nullptr);
	~WidgetControl() = default;

	void start() override;
	void setLibraryViewMode(LibraryViewModes view_mode);

	void updateFileNext(bool enabled, const QString& suffix = QString());
	void updateFilePrev(bool enabled, const QString& suffix = QString());

signals:
	void openFile();
	void openFileNext();
	void openFilePrev();
	void clearAll();

	void showDataList(bool on);
	void collapseDataList();
	void expandDataList();
	void setDataListViewMode(int view_mode);

	void showChart(bool on);
	void setChartViewMode(int view_mode);

private:
	void initWidgets();

	void updateViewMode();

private:
	QPushButton* _button_open = nullptr;
	QPushButton* _button_open_prev = nullptr;
	QPushButton* _button_open_next = nullptr;
	QPushButton* _button_clear = nullptr;

	Base::ButtonShow* _button_data_list = nullptr;
	Base::ButtonCollapse* _button_collapse_data_list = nullptr;
	Base::ButtonExpand* _button_expand_data_list = nullptr;
	Base::ComboBox* _combo_data_list_view_mode_library = nullptr;
	Base::ComboBox* _combo_data_list_view_mode_libraries = nullptr;

	Base::ButtonShow* _button_chart = nullptr;
	Base::ComboBox* _combo_chart_view_mode_library = nullptr;
	Base::ComboBox* _combo_chart_view_mode_libraries = nullptr;

	LibraryViewModes _view_mode = LibraryViewModes::Unknown;
};

} // namespace Player
