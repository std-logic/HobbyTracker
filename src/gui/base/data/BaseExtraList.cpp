#include "BaseExtraList.h"

Base::ExtraList::SublistsByStrings Base::ExtraList::extraByGroups() const
{
	SublistsByStrings list;
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
