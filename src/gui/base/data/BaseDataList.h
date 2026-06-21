#pragma once

#include <vector>

namespace Base
{

template <class T>
class DataList
{
public:
	DataList() = default;
	virtual ~DataList() = default;

	using ListContainer = std::vector<T>;
	using SubListContainer = std::vector<const T*>;

	ListContainer::iterator begin() noexcept
	{ return _data_list.begin(); }
	ListContainer::const_iterator begin() const noexcept
	{ return _data_list.begin(); }

	ListContainer::iterator end() noexcept
	{ return _data_list.end(); }
	ListContainer::const_iterator end() const noexcept
	{ return _data_list.end(); }

	inline T& operator[](size_t index)
	{ return _data_list[index]; }
	inline const T& operator[](size_t index) const
	{ return _data_list[index]; }

	auto size() const
	{ return _data_list.size(); }

	void add(const T& data)
	{ _data_list.push_back(data); }

protected:
	ListContainer _data_list;
};

} // namespace Base
