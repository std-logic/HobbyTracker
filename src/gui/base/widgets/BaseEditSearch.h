#pragma once

#include <QLineEdit>

class QTimer;

namespace Base
{

class EditSearch : public QLineEdit
{
	Q_OBJECT
public:
	explicit EditSearch(QWidget* parent = nullptr);
	virtual ~EditSearch() = default;

signals:
	void findText(const QString& search_text);

private slots:
	void onTextChanged(const QString& new_text);
	void onTimerDelay();

private:
	QString _search_text;
	QTimer* _timer_delay = nullptr;
};

} // namespace Base
