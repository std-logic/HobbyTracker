#pragma once

#include <QWidget>

class QHBoxLayout;

namespace Base
{

class ButtonSave;
class ButtonSettings;

class WidgetControl : public QWidget
{
	Q_OBJECT
public:
	explicit WidgetControl(QWidget* parent = nullptr);
	virtual ~WidgetControl() = default;

	virtual void start() = 0;

public slots:
	void highlightButtonSave(bool on);

signals:
	void saveCsvData();
	void showSettings();

protected:
	void addWidget(QWidget* widget, int stretch = 0, Qt::Alignment alignment = Qt::Alignment());
	void addStretch(int stretch = 0);
	void addSpacing(int size = 30);
	void addButtonSave();
	void addButtonSettings();

private:
	QHBoxLayout* _layout_main = nullptr;
	Base::ButtonSave* _button_save = nullptr;
	Base::ButtonSettings* _button_settings = nullptr;
};

} // namespace Base
