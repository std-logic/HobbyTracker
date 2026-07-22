#pragma once

#include "../common/PlayerCommon.h"
#include "../data/PlayerLibrary.h"
#include "../data/PlayerSettings.h"
#include "../storage/PlayerStorage.h"

#include <gui/base/widgets/BaseWidgetMain.h>

#include <QPointer>
#include <QElapsedTimer>

namespace Player
{

class WidgetControl;
class WidgetSummary;
class WidgetDataList;
class WidgetChart;
class WidgetSettings;

class WidgetMain : public Base::WidgetMain
{
	Q_OBJECT
public:
	explicit WidgetMain(QWidget* parent = nullptr);
	~WidgetMain() = default;

	static QString getName() { return tr("Плеер"); };

	void start() override;

private:
	void initWidgets();
	void initConnections();

	void updateFileContext(const QStringList& file_names = QStringList());
	void showReadingStart();
	void showReadingFinish();
	void setLibraryViewMode(LibraryViewModes view_mode);
	void readLibrary(const QStringList& file_names);
	void readLibraries(const QStringList& file_names);

private slots:
	void openFile();
	void openFileNext();
	void openFilePrev();
	void clearAll();

	void showSettings();
	void saveSettings(const Settings& settings);

	void updateAll();
	void updateSummary();
	void updateDataList();
	void updateChart();

private:
	WidgetControl* _widget_control = nullptr;
	WidgetSummary* _widget_summary = nullptr;
	WidgetDataList* _widget_data_list = nullptr;
	WidgetChart* _widget_chart = nullptr;
	QPointer<WidgetSettings> _widget_settings;

	Storage _storage;
	Settings _settings;
	Library _library;
	std::vector<Library> _libraries;
	LibraryViewModes _view_mode = LibraryViewModes::Unknown;

	QString _file_path;
	QStringList _file_entry_list;
	qsizetype _file_pos = -1;

	QElapsedTimer _reading_timer;
};

} // namespace Player
