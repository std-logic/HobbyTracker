#include "BaseWidgetFileEdit.h"

#include <common/Global.h>

#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QFileDialog>

Base::WidgetFileEdit::WidgetFileEdit(QWidget* parent)
	: QWidget{parent}
{
	initWidgets();
	setMode(ChooseMode::File);
}

void Base::WidgetFileEdit::setMode(ChooseMode mode)
{
	_mode = mode;
	_button_choose_file->setToolTip(tr("Выбрать %1...")
			.arg((_mode == ChooseMode::File) ? tr("файл") : tr("директорию")));
}

void Base::WidgetFileEdit::setFilter(const QString& filter)
{
	_filter = filter;
}

void Base::WidgetFileEdit::setStartDir(const QString& start_dir)
{
	_start_dir = start_dir;
}

void Base::WidgetFileEdit::setText(const QString& text)
{
	_edit_file->setText(text);
}

QString Base::WidgetFileEdit::text() const
{
	return _edit_file->text();
}

void Base::WidgetFileEdit::initWidgets()
{
	_layout_main = new QHBoxLayout(this);
	_layout_main->setContentsMargins(0, 0, 0, 0);
	_layout_main->setSpacing(Global::Sizes::default_spacing);

	_edit_file = new QLineEdit(this);
	_layout_main->addWidget(_edit_file);

	_button_choose_file = new QPushButton(QIcon::fromTheme(QIcon::ThemeIcon::FolderOpen), "", this);
	_button_choose_file->setFixedWidth(24);
	_button_choose_file->setFocusPolicy(Qt::NoFocus);
	connect(_button_choose_file, &QPushButton::clicked, this, &WidgetFileEdit::chooseFile);
	_layout_main->addWidget(_button_choose_file);
}

void Base::WidgetFileEdit::chooseFile()
{
	auto prev_name = _edit_file->text();
	auto curr_dir = !prev_name.isEmpty() ? (_start_dir + prev_name) : _start_dir;
	auto file_name = (_mode == ChooseMode::File) ?
			QFileDialog::getOpenFileName(
					this,
					tr("Выберите файл"),
					curr_dir,
					_filter) :
			QFileDialog::getExistingDirectory(
					this,
					tr("Выберите директорию"),
					curr_dir);
	if (file_name.isEmpty()) { return; }

	if (!_start_dir.isEmpty()) {
		file_name.remove(_start_dir);
	}

	_edit_file->setText(file_name);
}
