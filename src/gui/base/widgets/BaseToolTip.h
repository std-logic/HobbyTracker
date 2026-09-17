#pragma once

#include <QLabel>

class QTimer;

namespace Base
{

class ToolTip : public QLabel
{
	Q_OBJECT
public:
	enum class Mode
	{
		Text,
		Image,
	};

public:
	explicit ToolTip(QWidget* parent = nullptr);
	virtual ~ToolTip() = default;

	void setShowDelay(int ms) { _show_delay = ms; }

	void showText(const QString& text, Mode mode = Mode::Text, bool immediately = false);
	void hideText();

private slots:
	void onTimerDelay();

private:
	void update(const QString& text, Mode mode);
	void updatePos();

private:
	static constexpr QSize MAX_SIZE = QSize(750, 600);

	QString _text;
	Mode _mode = Mode::Text;
	QTimer* _timer_delay = nullptr;
	int _show_delay = 0;
};

} // namespace Base
