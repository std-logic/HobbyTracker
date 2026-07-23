#include "PlayerWidgetMain.h"
#include "PlayerWidgetControl.h"
#include "PlayerWidgetSummary.h"
#include "PlayerWidgetDataList.h"
#include "PlayerWidgetChart.h"
#include "PlayerWidgetSettings.h"

#include <QFileDialog>

Player::WidgetMain::WidgetMain(QWidget* parent)
	: Base::WidgetMain{parent}
{
	initWidgets();
	initConnections();
	updateFileContext();
}

void Player::WidgetMain::start()
{
	_widget_control->start();

	_settings.load();
}

void Player::WidgetMain::initWidgets()
{
	addWidget(_widget_control = new WidgetControl(this), 0, Qt::AlignTop);

	addWidget(_widget_summary = new WidgetSummary(this), 1, Qt::AlignTop);

	addWidget(_widget_data_list = new WidgetDataList(this), 100);

	addWidget(_widget_chart = new WidgetChart(this), 100);
}

void Player::WidgetMain::initConnections()
{
	connect(_widget_control, &WidgetControl::showDataList,
			_widget_data_list, &WidgetDataList::setVisible);
	connect(_widget_control, &WidgetControl::collapseDataList,
			_widget_data_list, &WidgetDataList::collapseAll);
	connect(_widget_control, &WidgetControl::expandDataList,
			_widget_data_list, &WidgetDataList::expandAll);
	connect(_widget_control, &WidgetControl::setDataListViewMode,
			_widget_data_list, &WidgetDataList::setViewMode);

	connect(_widget_control, &WidgetControl::showChart,
			_widget_chart, &WidgetChart::setVisible);
	connect(_widget_control, &WidgetControl::setChartViewMode,
			_widget_chart, &WidgetChart::setViewMode);

	connect(_widget_control, &WidgetControl::showSettings,
			this, &WidgetMain::showSettings);
	connect(_widget_control, &WidgetControl::openFile,
			this, &WidgetMain::openFile);
	connect(_widget_control, &WidgetControl::openFileNext,
			this, &WidgetMain::openFileNext);
	connect(_widget_control, &WidgetControl::openFilePrev,
			this, &WidgetMain::openFilePrev);
	connect(_widget_control, &WidgetControl::clearAll,
			this, &WidgetMain::clearAll);

	connect(_widget_data_list, &WidgetDataList::needUpdate,
			this, &WidgetMain::updateDataList);

	connect(_widget_chart, &WidgetChart::needUpdate,
			this, &WidgetMain::updateChart);
}

void Player::WidgetMain::updateFileContext(const QStringList& file_names)
{
	if (file_names.size() != 1) {
		_file_path.clear();
		_file_entry_list.clear();
		_file_pos = -1;
		_widget_control->updateFileNext(false);
		_widget_control->updateFilePrev(false);
	} else {
		// split full name at file name and path
		QFileInfo file_info(file_names[0]);
		auto file_path = file_info.absolutePath();
		auto file_name = file_info.fileName();

		// find all *.xml files in current directory (but only when directory changed)
		if (_file_path != file_path) {
			_file_path = file_path;
			QDir dir(file_path);
			auto filter = QStringList() << QStringLiteral("*.xml");
			_file_entry_list = dir.entryList(filter, QDir::Files, QDir::Name);
		}

		// find next and previous files according to the current file
		_file_pos = _file_entry_list.indexOf(file_name);
		if (_file_pos != -1) {
			if (_file_pos < (_file_entry_list.size() - 1)) {
				auto next_file_name = _file_entry_list[_file_pos + 1];
				next_file_name.remove(QStringLiteral("winamp_")).remove(QStringLiteral(".xml"));
				_widget_control->updateFileNext(true, QStringLiteral(": ") + next_file_name);
			} else {
				_widget_control->updateFileNext(false);
			}
			if (_file_pos > 0) {
				auto prev_file_name = _file_entry_list[_file_pos - 1];
				prev_file_name.remove(QStringLiteral("winamp_")).remove(QStringLiteral(".xml"));
				_widget_control->updateFilePrev(true, QStringLiteral(": ") + prev_file_name);
			} else {
				_widget_control->updateFilePrev(false);
			}
		} else {
			_widget_control->updateFileNext(false);
			_widget_control->updateFilePrev(false);
		}
	}
}

void Player::WidgetMain::showReadingStart()
{
	_reading_timer.start();
}

void Player::WidgetMain::showReadingFinish()
{
	emit showMessage(tr("Библиотека загружена за %1 мс").arg(_reading_timer.elapsed()), 10000);
}

void Player::WidgetMain::setLibraryViewMode(LibraryViewModes view_mode)
{
	if (_view_mode == view_mode) { return; }
	_view_mode = view_mode;

	_widget_control->setLibraryViewMode(_view_mode);
}

void Player::WidgetMain::readLibrary(const QStringList& file_names)
{
	showReadingStart();
	_libraries.clear();
	setLibraryViewMode(LibraryViewModes::Library);
	_library = _storage.readLibrary(file_names);
	updateAll();
	showReadingFinish();
}

void Player::WidgetMain::readLibraries(const QStringList& file_names)
{
	showReadingStart();
	_library.clear();
	setLibraryViewMode(LibraryViewModes::Libraries);
	_libraries = _storage.readLibraries(file_names);
	updateAll();
	showReadingFinish();
}

void Player::WidgetMain::openFile()
{
	auto file_names = QFileDialog::getOpenFileNames(
			this,
			tr("Выберите один или несколько файлов базы данных"),
			_settings.defaultDir(),
			QStringLiteral("XML files (*.xml)"));
	if (file_names.isEmpty()) { return; }

	file_names.sort();
	updateFileContext(file_names);
	if (file_names.size() <= 2) {
		readLibrary(file_names);
	} else {
		readLibraries(file_names);
	}
}

void Player::WidgetMain::openFileNext()
{
	if ((_file_pos < 0) || (_file_pos >= (_file_entry_list.size() - 1))) { return; }
	auto file_names = QStringList() << (_file_path + "/" + _file_entry_list[_file_pos + 1]);
	updateFileContext(file_names);
	readLibrary(file_names);
}

void Player::WidgetMain::openFilePrev()
{
	if ((_file_pos < 1) || (_file_pos >= _file_entry_list.size())) { return; }
	auto file_names = QStringList() << (_file_path + "/" + _file_entry_list[_file_pos - 1]);
	updateFileContext(file_names);
	readLibrary(file_names);
}

void Player::WidgetMain::clearAll()
{
	_library.clear();
	_libraries.clear();
	_widget_summary->clear();
	_widget_data_list->clear();
	_widget_chart->clearChart();
	setLibraryViewMode(LibraryViewModes::Unknown);
	updateFileContext();
}

void Player::WidgetMain::showSettings()
{
	if (!_widget_settings) {
		_widget_settings = new WidgetSettings(_settings, this);
		connect(_widget_settings, &WidgetSettings::saveSettings,
				this, &WidgetMain::saveSettings);
	}
	_widget_settings->open();
}

void Player::WidgetMain::saveSettings(const Settings& settings)
{
	_settings = settings;
	_settings.save();
	emit showMessage(tr("Настройки сохранены"));
}

void Player::WidgetMain::updateAll()
{
	updateSummary();
	updateDataList();
	updateChart();
}

void Player::WidgetMain::updateSummary()
{
	if (_view_mode == LibraryViewModes::Library) {
		_widget_summary->update(_library);
	} else if (_view_mode == LibraryViewModes::Libraries) {
		_widget_summary->update(_libraries);
	}
}

void Player::WidgetMain::updateDataList()
{
	if (_view_mode == LibraryViewModes::Library) {
		_widget_data_list->update(_library);
	} else if (_view_mode == LibraryViewModes::Libraries) {
		_widget_data_list->update(_libraries);
	}
}

void Player::WidgetMain::updateChart()
{
	if (_view_mode == LibraryViewModes::Library) {
		_widget_chart->update(_library);
	} else if (_view_mode == LibraryViewModes::Libraries) {
		_widget_chart->update(_libraries);
	}
}
