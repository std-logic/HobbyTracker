#include "BaseExtraList.h"

void Base::ExtraList::sort()
{
	std::ranges::sort(_data_list, {}, [](const Extra& extra) {
		return std::make_tuple(extra.group(), extra.title());
	});
}

Base::ExtraList::SublistsByStrings Base::ExtraList::extraByGroups() const
{
	return sublistsByStrings(&Extra::group);
}

Base::ExtraList::ListOfStrings Base::ExtraList::listOfGroups() const
{
	return listOfStrings(&Extra::group);
}

Base::ExtraList::Synonyms Base::ExtraList::getSynonyms(const QString& group) const
{
	Synonyms synonyms;
	for (const auto& extra : _data_list) {
		if (extra.group() == group) {
			auto names = extra.title().split(", ", Qt::SkipEmptyParts);
			for (const auto& name : names) {
				synonyms[name] = extra.notes();
			}
		}
	}
	return synonyms;
}

Base::ExtraList::Favorites Base::ExtraList::getFavorites(const QString& group) const
{
	Favorites favorites;
	for (const auto& extra : _data_list) {
		if (extra.group() == group) {
			favorites.insert(extra.title());
		}
	}
	return favorites;
}
