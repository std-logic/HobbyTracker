#pragma once

#include <QComboBox>

namespace Base
{

class ComboBox : public QComboBox
{
	Q_OBJECT
public:
	explicit ComboBox(QWidget* parent = nullptr);
	virtual ~ComboBox() = default;

signals:
	void currentDataChanged(int data);
};

} // namespace Base
