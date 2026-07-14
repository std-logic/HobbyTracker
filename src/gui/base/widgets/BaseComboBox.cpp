#include "BaseComboBox.h"

Base::ComboBox::ComboBox(QWidget* parent)
	: QComboBox{parent}
{
	connect(this, &QComboBox::currentIndexChanged, this, [this](int index) {
		emit currentDataChanged(itemData(index).toInt());
	});
}
