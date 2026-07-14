#pragma once

#include "BaseButtonAdd.h"
#include "BaseButtonCollapse.h"
#include "BaseButtonExpand.h"
#include "BaseButtonShow.h"
#include "BaseComboBox.h"

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

	template<typename FuncShow>
	void addButtonShow(ButtonShow*& button, const QString& text, FuncShow&& func_show)
	{
		addWidget(button = new ButtonShow(text, this));
		connect(button, &ButtonShow::toggled, this, func_show);
	}

	template<typename FuncAdd>
	void addButtonAdd(ButtonAdd*& button, FuncAdd&& func_add)
	{
		addWidget(button = new ButtonAdd(this));
		connect(button, &ButtonAdd::clicked, this, func_add);
	}

	template<typename FuncCollapse>
	void addButtonCollapse(ButtonCollapse*& button, FuncCollapse&& func_collapse)
	{
		addWidget(button = new ButtonCollapse(this));
		connect(button, &ButtonCollapse::clicked, this, func_collapse);
	}

	template<typename FuncExpand>
	void addButtonExpand(ButtonExpand*& button, FuncExpand&& func_expand)
	{
		addWidget(button = new ButtonExpand(this));
		connect(button, &ButtonExpand::clicked, this, func_expand);
	}

	template<typename FuncIndexChanged>
	void addComboBox(ComboBox*& combo, FuncIndexChanged&& func_data_changed,
			const std::vector<std::pair<QString, int>>& items)
	{
		addWidget(combo = new ComboBox(this));
		for (const auto& [text, data] : items) { combo->addItem(text, data); }
		connect(combo, &ComboBox::currentDataChanged, this, func_data_changed);
	}

private:
	QHBoxLayout* _layout_main = nullptr;
	ButtonSave* _button_save = nullptr;
	ButtonSettings* _button_settings = nullptr;
};

} // namespace Base
