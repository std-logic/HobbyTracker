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

	Synonyms getSynonyms(const QString& group) const;
	Favorites getFavorites(const QString& group) const;
};

} // namespace Base
