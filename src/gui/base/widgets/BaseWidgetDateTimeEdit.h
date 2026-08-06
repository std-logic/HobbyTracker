#pragma once

#include <QWidget>

class QHBoxLayout;
class QPushButton;
class QLineEdit;

namespace Base
{

class WidgetDateTimeEdit : public QWidget
{
	Q_OBJECT
public:
	explicit WidgetDateTimeEdit(QWidget* parent = nullptr);
	virtual ~WidgetDateTimeEdit() = default;

	void setText(const QString& text);
	QString text() const;
	bool isValid() const;

private:
	void initWidgets();

private slots:
	void setCurrDate();

private:
	QHBoxLayout* _layout_main = nullptr;
	QLineEdit* _edit_date = nullptr;
	QPushButton* _button_curr = nullptr;
};

} // namespace Base
