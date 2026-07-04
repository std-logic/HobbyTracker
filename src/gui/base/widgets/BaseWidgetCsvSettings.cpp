#include "BaseWidgetCsvSettings.h"

#include <common/Global.h>

#include <QGridLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>
#include <QLabel>
#include <QFileDialog>

Base::WidgetCsvSettings::WidgetCsvSettings(const Csv::Settings& csv_settings, QWidget* parent)
	: QGroupBox{parent}
	, _csv_settings{csv_settings}
{
	initCommonParams();
	initWidgets();
	copySettingsToGui();
}

Csv::Settings Base::WidgetCsvSettings::getSettings()
{
	copyGuiToSettings();

	return _csv_settings;
}

void Base::WidgetCsvSettings::initCommonParams()
{
	setTitle(tr("База данных"));
}

void Base::WidgetCsvSettings::initWidgets()
{
	_layout_main = new QGridLayout(this);
	_layout_main->setContentsMargins(Global::Sizes::default_margin);
	_layout_main->setSpacing(Global::Sizes::default_spacing);

	auto row_count = _layout_main->rowCount();
	auto num_of_files = _csv_settings.numOfFiles();

	for (size_t i = 0; i < num_of_files; ++i) {
		auto layout_file_name = new QHBoxLayout();
		layout_file_name->setContentsMargins(0, 0, 0, 0);
		layout_file_name->setSpacing(Global::Sizes::default_spacing);

		_edit_file_name.emplace_back(new QLineEdit(this));
		layout_file_name->addWidget(_edit_file_name.back());

		_button_choose_file.emplace_back(
				new QPushButton(QIcon::fromTheme(QIcon::ThemeIcon::FolderOpen), "", this));
		_button_choose_file.back()->setToolTip(tr("Выбрать файл..."));
		_button_choose_file.back()->setFixedWidth(24);
		_button_choose_file.back()->setFocusPolicy(Qt::NoFocus);
		connect(_button_choose_file.back(), &QPushButton::clicked, this, [this,i]() {
			chooseFile(i);
		});
		layout_file_name->addWidget(_button_choose_file.back());

		_layout_main->addLayout(layout_file_name, row_count, 0, 1, 2);

		++row_count;
	}

	auto label_encoding = new QLabel(tr("Кодировка:"), this);
	label_encoding->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
	_layout_main->addWidget(label_encoding, row_count, 0);

	_combo_encoding = new QComboBox(this);
	_combo_encoding->addItem(tr("UTF-8"), static_cast<int>(QStringConverter::Utf8));
	_combo_encoding->addItem(tr("UTF-16"), static_cast<int>(QStringConverter::Utf16));
	_combo_encoding->addItem(tr("UTF-16LE"), static_cast<int>(QStringConverter::Utf16LE));
	_combo_encoding->addItem(tr("UTF-16BE"), static_cast<int>(QStringConverter::Utf16BE));
	_combo_encoding->addItem(tr("UTF-32"), static_cast<int>(QStringConverter::Utf32));
	_combo_encoding->addItem(tr("UTF-32LE"), static_cast<int>(QStringConverter::Utf32LE));
	_combo_encoding->addItem(tr("UTF-32BE"), static_cast<int>(QStringConverter::Utf32BE));
	_combo_encoding->addItem(tr("Latin1"), static_cast<int>(QStringConverter::Latin1));
	_layout_main->addWidget(_combo_encoding, row_count, 1);

	++row_count;

	auto label_delimiter = new QLabel(tr("Разделитель:"), this);
	label_delimiter->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
	_layout_main->addWidget(label_delimiter, row_count, 0);

	_combo_delimiter = new QComboBox(this);
	_combo_delimiter->addItem(tr(","), QChar(','));
	_combo_delimiter->addItem(tr(";"), QChar(';'));
	_combo_delimiter->addItem(tr("|"), QChar('|'));
	_combo_delimiter->addItem(tr("Tab"), QChar('\t'));
	_layout_main->addWidget(_combo_delimiter, row_count, 1);

	++row_count;

	auto label_skip_at_start = new QLabel(tr("Сдвиг данных:"), this);
	label_skip_at_start->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
	_layout_main->addWidget(label_skip_at_start, row_count, 0);

	_edit_skip_at_start = new QLineEdit(this);
	_edit_skip_at_start->setToolTip(tr("Номер строки, с которой начинаются данные (0 - без сдвига)"));
	_edit_skip_at_start->setValidator(new QIntValidator(0, INT_MAX, _edit_skip_at_start));
	_layout_main->addWidget(_edit_skip_at_start, row_count, 1);

	++row_count;

	_button_load_data = new QPushButton(tr("Прочитать данные"), this);
	_button_load_data->setFocusPolicy(Qt::NoFocus);
	connect(_button_load_data, &QPushButton::clicked,
			this, &WidgetCsvSettings::loadData);
	_layout_main->addWidget(_button_load_data, row_count, 0, 1, 2);
}

void Base::WidgetCsvSettings::copySettingsToGui()
{
	auto num_of_files = _csv_settings.numOfFiles();
	for (size_t i = 0; i < num_of_files; ++i) {
		_edit_file_name[i]->setText(_csv_settings.fileName(i));
	}

	_combo_encoding->setCurrentIndex(
			_combo_encoding->findData(static_cast<int>(_csv_settings.encoding())));

	_combo_delimiter->setCurrentIndex(
			_combo_delimiter->findData(_csv_settings.delimiter()));

	_edit_skip_at_start->setText(QString::number(_csv_settings.skipAtStart()));
}

void Base::WidgetCsvSettings::copyGuiToSettings()
{
	auto num_of_files = _csv_settings.numOfFiles();
	for (size_t i = 0; i < num_of_files; ++i) {
		_csv_settings.setFileName(i, _edit_file_name[i]->text());
	}

	_csv_settings.setEncoding(
			static_cast<QStringConverter::Encoding>(_combo_encoding->currentData().toInt()));

	_csv_settings.setDelimiter(_combo_delimiter->currentData().toChar());

	auto skip_at_start_str = _edit_skip_at_start->text();
	if (!skip_at_start_str.isEmpty()) {
		_csv_settings.setSkipAtStart(skip_at_start_str.toInt());
	} else {
		_edit_skip_at_start->setText(QString::number(_csv_settings.skipAtStart()));
	}
}

void Base::WidgetCsvSettings::chooseFile(size_t index)
{
	auto file_name = QFileDialog::getOpenFileName(
			this,
			tr("Выберите файл базы данных"),
			_edit_file_name[index]->text(),
			QStringLiteral("CSV files (*.csv)"));

	if (file_name.isEmpty()) {
		return;
	}

	_edit_file_name[index]->setText(file_name);
}

void Base::WidgetCsvSettings::loadData()
{
	copyGuiToSettings();

	emit readCsvData(_csv_settings);
}
