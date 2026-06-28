#pragma once

#include <QDialog>

class QGridLayout;
class QPushButton;

namespace Base
{

class WidgetSettings : public QDialog
{
	Q_OBJECT
public:
	explicit WidgetSettings(QWidget* parent = nullptr);
	virtual ~WidgetSettings() = default;

	void addWidget(QWidget* widget);
	void addWidget(const QString& label_text, QWidget* widget);
	void addLayout(QLayout* layout);
	void addLayout(const QString& label_text, QLayout* layout);

	void addStandardButtons();

protected slots:
	virtual void save() = 0;

private:
	void initCommonParams();
	void initWidgets();

private:
	QGridLayout* _layout_main = nullptr;
	QPushButton* _button_save = nullptr;
	QPushButton* _button_exit = nullptr;
};

} // namespace Base
