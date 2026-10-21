#pragma once

#include "BaseFlowContainer.h"

class QLineEdit;

namespace Base
{

class FlowWithLineEdit : public FlowContainer
{
	Q_OBJECT
public:
	explicit FlowWithLineEdit(QWidget* parent = nullptr);
	virtual ~FlowWithLineEdit() = default;

	void setValues(const QStringList& texts, bool add_one_if_empty = false);
	QStringList values() const;
	bool isValid() const;
	QLineEdit* lineEditAt(int index) const;

public slots:
	void addLineEdit(const QString& text);
};

} // namespace Base
