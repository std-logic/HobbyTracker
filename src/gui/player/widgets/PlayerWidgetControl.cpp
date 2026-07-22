#include "PlayerWidgetControl.h"

Player::WidgetControl::WidgetControl(QWidget* parent)
	: Base::WidgetControl{parent}
{
	initWidgets();
}

void Player::WidgetControl::start()
{
	updateViewMode();
}

void Player::WidgetControl::setLibraryViewMode(LibraryViewModes view_mode)
{
	if (_view_mode == view_mode) { return; }
	_view_mode = view_mode;

	updateViewMode();
}

void Player::WidgetControl::updateFileNext(bool enabled, const QString& suffix)
{
	_button_open_next->setToolTip(tr("Открыть следующий файл") + suffix);
	_button_open_next->setEnabled(enabled);
}

void Player::WidgetControl::updateFilePrev(bool enabled, const QString& suffix)
{
	_button_open_prev->setToolTip(tr("Открыть предыдущий файл") + suffix);
	_button_open_prev->setEnabled(enabled);
}

void Player::WidgetControl::initWidgets()
{
	// open/clear
	{
		addButton(_button_open, tr("Открыть..."), &WidgetControl::openFile);

		addButton(_button_open_prev, QIcon::fromTheme(QIcon::ThemeIcon::GoPrevious), "",
				  &WidgetControl::openFilePrev);
		_button_open_prev->setToolTip(tr("Открыть предыдущий файл"));
		_button_open_prev->setFixedWidth(24);

		addButton(_button_open_next, QIcon::fromTheme(QIcon::ThemeIcon::GoNext), "",
				  &WidgetControl::openFileNext);
		_button_open_next->setToolTip(tr("Открыть следующий файл"));
		_button_open_next->setFixedWidth(24);

		addButton(_button_clear, QIcon::fromTheme(QIcon::ThemeIcon::ViewRefresh), "",
				  &WidgetControl::clearAll);
		_button_clear->setToolTip(tr("Очистить"));
		_button_clear->setFixedWidth(24);
	}

	// data list
	{
		addSpacing();
		addButtonShow(_button_data_list, tr("Список"), &WidgetControl::showDataList);
		addButtonCollapse(_button_collapse_data_list, &WidgetControl::collapseDataList);
		addButtonExpand(_button_expand_data_list, &WidgetControl::expandDataList);
		addComboBox(_combo_data_list_view_mode_library, &WidgetControl::setDataListViewMode, {
				{tr("По группам"), static_cast<int>(DataListViewModes::ByArtists)},
				{tr("По альбомам"), static_cast<int>(DataListViewModes::ByAlbums)},
				{tr("По трекам"), static_cast<int>(DataListViewModes::ByTracks)},
				{tr("По лучшим трекам"), static_cast<int>(DataListViewModes::ByBestTracks)},
				{tr("По жанрам"), static_cast<int>(DataListViewModes::ByGenres)},
				{tr("Сводка"), static_cast<int>(DataListViewModes::Summary)},
		});
		addComboBox(_combo_data_list_view_mode_libraries, &WidgetControl::setDataListViewMode, {
				{tr("История"), static_cast<int>(DataListViewModes::History)},
		});

		_button_data_list->addSlaveWidgets({
			_button_collapse_data_list,
			_button_expand_data_list,
			_combo_data_list_view_mode_library,
			_combo_data_list_view_mode_libraries,
		});
	}

	// chart
	{
		addSpacing();
		addButtonShow(_button_chart, tr("Статистика"), &WidgetControl::showChart);
		addComboBox(_combo_chart_view_mode_library, &WidgetControl::setChartViewMode, {
				{tr("По прослушиваниям"), static_cast<int>(ChartViewModes::ByPlayCounts)},
				{tr("По десятилетиям"), static_cast<int>(ChartViewModes::ByDecades)},
		});
		addComboBox(_combo_chart_view_mode_libraries, &WidgetControl::setChartViewMode, {
				{tr("Прирост прослушиваний"), static_cast<int>(ChartViewModes::HistoryPlayCounts)},
				{tr("Прирост групп"), static_cast<int>(ChartViewModes::HistoryArtists)},
				{tr("Прирост альбомов"), static_cast<int>(ChartViewModes::HistoryAlbums)},
				{tr("Прирост треков"), static_cast<int>(ChartViewModes::HistoryTracks)},
		});

		_button_chart->addSlaveWidgets({
			_combo_chart_view_mode_library,
			_combo_chart_view_mode_libraries,
		});
	}

	addButtonSettings();
}

void Player::WidgetControl::updateViewMode()
{
	_button_clear->setEnabled(_view_mode != LibraryViewModes::Unknown);

	_button_data_list->setEnabled(_view_mode != LibraryViewModes::Unknown);
	_button_data_list->setChecked(_view_mode != LibraryViewModes::Unknown);

	_button_chart->setEnabled(_view_mode != LibraryViewModes::Unknown);
	if (_view_mode == LibraryViewModes::Unknown) { _button_chart->setChecked(false); }

	_combo_data_list_view_mode_library->setVisible(_view_mode == LibraryViewModes::Library);
	_combo_data_list_view_mode_libraries->setVisible(_view_mode == LibraryViewModes::Libraries);
	_combo_chart_view_mode_library->setVisible(_view_mode == LibraryViewModes::Library);
	_combo_chart_view_mode_libraries->setVisible(_view_mode == LibraryViewModes::Libraries);

	switch (_view_mode) {
		case LibraryViewModes::Library:
			_combo_data_list_view_mode_libraries->setCurrentIndex(-1);
			_combo_data_list_view_mode_library->setCurrentIndex(0);
			_combo_chart_view_mode_libraries->setCurrentIndex(-1);
			_combo_chart_view_mode_library->setCurrentIndex(0);
		break;
		case LibraryViewModes::Libraries:
			_combo_data_list_view_mode_library->setCurrentIndex(-1);
			_combo_data_list_view_mode_libraries->setCurrentIndex(0);
			_combo_chart_view_mode_library->setCurrentIndex(-1);
			_combo_chart_view_mode_libraries->setCurrentIndex(0);
		break;
		default:
			_combo_data_list_view_mode_library->setCurrentIndex(-1);
			_combo_data_list_view_mode_libraries->setCurrentIndex(-1);
			_combo_chart_view_mode_library->setCurrentIndex(-1);
			_combo_chart_view_mode_libraries->setCurrentIndex(-1);
		break;
	}
}
