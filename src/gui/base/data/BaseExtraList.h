#pragma once

#include "BaseExtra.h"
#include "BaseDataList.h"

#include <unordered_map>

namespace Base
{

class ExtraList : public DataList<Extra>
{
public:
	ExtraList() = default;

	using ExtraByGroups = std::unordered_map<QString, SubListContainer>;
	ExtraByGroups extraByGroups() const;
	ListOfStrings listOfGroups() const;

	int findIndexById(const QString& id);
};

} // namespace Base
