#include "BaseFlowPlaceholder.h"

Base::FlowPlaceholder::FlowPlaceholder(const QSize& size, QWidget* parent)
	: QFrame{parent}
{
	setFixedSize(size);
	setAttribute(Qt::WA_TransparentForMouseEvents);
	setStyleSheet(
		"QFrame{"
		"background-color: rgb(230,230,230);"
		"border: 2px dashed rgb(175,175,175);"
		"}"
	);
}
