#include "BaseExtraList.h"

Base::ExtraList::SublistsByStrings Base::ExtraList::extraByGroups() const
{
	return sublistsByStrings(&Extra::group);
}

Base::ExtraList::ListOfStrings Base::ExtraList::listOfGroups() const
{
	return listOfStrings(&Extra::group);
}
