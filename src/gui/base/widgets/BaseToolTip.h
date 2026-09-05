#pragma once

#include <QLabel>

class QTimer;

namespace Base
{

class ToolTip : public QLabel
{
	Q_OBJECT
public:
	explicit ToolTip(QWidget* parent = nullptr);
	virtual ~ToolTip() = default;

	void setShowDelay(int ms) { _show_delay = ms; }

	void showText(const QString& text);
	void hideText();

private slots:
	void onTimerDelay();

private:
	void update(const QString& text);
	void updatePos();

private:
	QString _text;
	QTimer* _timer_delay = nullptr;
	int _show_delay = 0;
};

} // namespace Base
