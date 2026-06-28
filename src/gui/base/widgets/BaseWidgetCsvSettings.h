#pragma once

#include <storage/csv/CsvSettings.h>

#include <QGroupBox>

class QGridLayout;
class QHBoxLayout;
class QPushButton;
class QLineEdit;
class QComboBox;

namespace Base
{

class WidgetCsvSettings : public QGroupBox
{
	Q_OBJECT
public:
	explicit WidgetCsvSettings(const Csv::Settings& csv_settings, QWidget* parent = nullptr);
	virtual ~WidgetCsvSettings() = default;

	Csv::Settings getSettings();

signals:
	void readCsvData(const Csv::Settings& csv_settings);

private:
	void initCommonParams();
	void initWidgets();
	void copySettingsToGui();
	void copyGuiToSettings();

private slots:
	void chooseFile();
	void loadData();
	
private:
	QGridLayout* _layout_main = nullptr;
	QLineEdit* _edit_file_name = nullptr;
	QPushButton* _button_choose_file = nullptr;
	QComboBox* _combo_encoding = nullptr;
	QComboBox* _combo_delimiter = nullptr;
	QLineEdit* _edit_skip_at_start = nullptr;
	QPushButton* _button_load_data = nullptr;

	Csv::Settings _csv_settings;
};

} // namespace Base
