#pragma once

#include "BaseExtra.h"
#include "BaseDataList.h"

namespace Base
{

class ExtraList : public DataList<Extra>
{
public:
	ExtraList() = default;

	SublistsByStrings extraByGroups() const;
	ListOfStrings listOfGroups() const;
};

} // namespace Base
