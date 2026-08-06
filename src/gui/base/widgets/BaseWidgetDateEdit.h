#pragma once

#include <QWidget>

class QHBoxLayout;
class QPushButton;
class QLineEdit;

namespace Base
{

class WidgetDateEdit : public QWidget
{
	Q_OBJECT
public:
	explicit WidgetDateEdit(QWidget* parent = nullptr);
	virtual ~WidgetDateEdit() = default;

	void setText(const QString& text);
	QString text() const;
	bool isValid() const;

private:
	void initWidgets();

private slots:
	void setCurrDate();
	void setPrevDate();
	void setNextDate();

private:
	QHBoxLayout* _layout_main = nullptr;
	QLineEdit* _edit_date = nullptr;
	QPushButton* _button_curr = nullptr;
	QPushButton* _button_prev = nullptr;
	QPushButton* _button_next = nullptr;
};

} // namespace Base
