#pragma once

#include <QComboBox>

#include <set>

namespace Base
{

class ComboEdit : public QComboBox
{
	Q_OBJECT
public:
	explicit ComboEdit(QWidget* parent = nullptr);
	virtual ~ComboEdit() = default;

	void addList(const std::set<QString>& list_of_strings, bool choose_if_single = false);
	void setTextAndList(const QString& text, const std::set<QString>& list_of_strings);

signals:

};

} // namespace Base
