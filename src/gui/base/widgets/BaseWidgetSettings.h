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

protected slots:
	virtual void save() = 0;

protected:
	void addWidget(QWidget* widget);
	void addWidget(const QString& label_text, QWidget* widget);
	void addLayout(QLayout* layout);
	void addLayout(const QString& label_text, QLayout* layout);

	template<std::derived_from<QWidget> T>
	void add(T*& widget)
	{
		widget = new T(this);
		addWidget(widget);
	}

	template<std::derived_from<QWidget> T>
	void add(const QString& label_text, T*& widget)
	{
		widget = new T(this);
		addWidget(label_text, widget);
	}

private:
	void initCommonParams();
	void initWidgets();

private:
	QGridLayout* _layout_main = nullptr;
	QPushButton* _button_save = nullptr;
	QPushButton* _button_exit = nullptr;
};

} // namespace Base
