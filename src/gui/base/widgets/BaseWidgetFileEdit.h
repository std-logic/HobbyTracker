#pragma once

#include <QWidget>

class QHBoxLayout;
class QPushButton;
class QLineEdit;

namespace Base
{

class WidgetFileEdit : public QWidget
{
	Q_OBJECT
public:
	enum class ChooseMode
	{
		File,
		Dir,
	};

public:
	explicit WidgetFileEdit(QWidget* parent = nullptr);
	virtual ~WidgetFileEdit() = default;

	void setMode(ChooseMode mode);
	void setFilter(const QString& filter);
	void setStartDir(const QString& start_dir);

	void setText(const QString& text);
	QString text() const;

private:
	void initWidgets();

private slots:
	void chooseFile();

private:
	QHBoxLayout* _layout_main = nullptr;
	QLineEdit* _edit_file = nullptr;
	QPushButton* _button_choose_file = nullptr;

	ChooseMode _mode = ChooseMode::File;
	QString _filter;
	QString _start_dir;
};

} // namespace Base
