#include "BaseExtraList.h"

Base::ExtraList::ExtraByGroups Base::ExtraList::extraByGroups() const
{
	ExtraByGroups list;
	for (const auto& data : _data_list) {
		list[data.group()].push_back(&data);
	}
	return list;
}

Base::ExtraList::ListOfStrings Base::ExtraList::listOfGroups() const
{
	ListOfStrings list;
	for (const auto& data : _data_list) {
		list.insert(data.group());
	}
	return list;
}

int Base::ExtraList::findIndexById(const QString& id)
{
	for (size_t i = 0; i < _data_list.size(); ++i) {
		if (id == _data_list[i].id()) {
			return i;
		}
	}
	return -1;
}
