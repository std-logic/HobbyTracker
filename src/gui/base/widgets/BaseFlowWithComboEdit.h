#pragma once

#include "BaseFlowContainer.h"

#include <set>

namespace Base
{

class ComboEdit;

class FlowWithComboEdit : public FlowContainer
{
	Q_OBJECT
public:
	explicit FlowWithComboEdit(QWidget* parent = nullptr);
	virtual ~FlowWithComboEdit() = default;

	void setList(const std::set<QString>& list_of_strings);
	void setValues(const QStringList& texts);
	QStringList values() const;
	ComboEdit* comboEditAt(int index) const;

public slots:
	void addComboEdit(const QString& text);

private:
	std::set<QString> _list_of_strings;
};

} // namespace Base
