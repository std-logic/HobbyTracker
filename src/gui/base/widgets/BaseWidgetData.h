#pragma once

#include <QDialog>

class QGridLayout;
class QPushButton;

namespace Base
{

class WidgetData : public QDialog
{
	Q_OBJECT
public:
	explicit WidgetData(size_t index, size_t data_size, QWidget* parent = nullptr);
	virtual ~WidgetData() = default;

signals:
	void showMessage(const QString& text, int timeout = 5000);

protected slots:
	virtual void save() = 0;

protected:
	void addWidget(QWidget* widget);
	void addWidget(const QString& label_text, QWidget* widget);
	void addLayout(QLayout* layout);
	void addLayout(const QString& label_text, QLayout* layout);

private:
	void initCommonParams();
	void initWidgets();

protected:
	size_t _index = 0;
	bool _mode_edit_data = false;

private:
	QGridLayout* _layout_main = nullptr;
	QPushButton* _button_save = nullptr;
	QPushButton* _button_exit = nullptr;
};

} // namespace Base
