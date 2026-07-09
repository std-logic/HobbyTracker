#pragma once

#include "BaseData.h"

#include <common/Helper.h>

#include <vector>
#include <unordered_map>
#include <map>
#include <set>

namespace Base
{

template <std::derived_from<Data> T>
class DataList
{
public:
	DataList() = default;
	virtual ~DataList() = default;

	using ListContainer = std::vector<T>;
	using SubListContainer = std::vector<const T*>;
	using SublistsByStrings = std::unordered_map<QString, SubListContainer>;
	using SublistsByIntegers = std::unordered_map<uint32_t, SubListContainer>;
	using NumbersByStrings = std::map<QString, uint32_t>;
	using NumbersByIntegers = std::map<uint32_t, uint32_t>;
	using ListOfStrings = std::set<QString>;
	using DataMethodReturningString = QString (T::*)() const;
	using DataMethodReturningStringList = QStringList (T::*)() const;
	using DataMethodReturningInteger = uint32_t (T::*)() const;

	ListContainer::iterator begin() noexcept
	{ return _data_list.begin(); }
	ListContainer::const_iterator begin() const noexcept
	{ return _data_list.begin(); }

	ListContainer::iterator end() noexcept
	{ return _data_list.end(); }
	ListContainer::const_iterator end() const noexcept
	{ return _data_list.end(); }

	inline T& operator[](size_t index) noexcept
	{ return _data_list[index]; }
	inline const T& operator[](size_t index) const noexcept
	{ return _data_list[index]; }

	inline auto size() const noexcept
	{ return _data_list.size(); }

	inline bool empty() const noexcept
	{ return _data_list.empty(); }

	inline void add(const T& data)
	{ _data_list.push_back(data); }

	inline void del(size_t index)
	{ _data_list.erase(_data_list.begin() + index); }

	int findIndexById(const QString& id)
	{
		for (size_t i = 0; i < _data_list.size(); ++i) {
			if (id == _data_list[i].id()) { return i; }
		}
		return -1;
	}

	// Return items, grouped by string values from method (typical for using in WidgetTree)
	SublistsByStrings sublistsByStrings(DataMethodReturningString method) const
	{
		SublistsByStrings list;
		for (const auto& data : _data_list) {
			list[(data.*method)()].push_back(&data);
		}
		return list;
	}

	// Return items, grouped by string values from method (typical for using in WidgetTree)
	SublistsByStrings sublistsByStrings(DataMethodReturningStringList method) const
	{
		SublistsByStrings list;
		for (const auto& data : _data_list) {
			auto str_list = (data.*method)();
			for (const auto& str : str_list) {
				list[str].push_back(&data);
			}
		}
		return list;
	}

	// Return items, grouped by epoch strings (years, decades, centuries) from method
	SublistsByStrings sublistsByEpochStrings(DataMethodReturningInteger method, uint32_t step) const
	{
		SublistsByStrings list;
		for (const auto& data : _data_list) {
			list[Helper::epochString((data.*method)(), step)].push_back(&data);
		}
		return list;
	}

	// Return items, grouped by integer values from method (typical for using in WidgetTree)
	SublistsByIntegers sublistsByIntegers(DataMethodReturningInteger method) const
	{
		SublistsByIntegers list;
		for (const auto& data : _data_list) {
			list[(data.*method)()].push_back(&data);
		}
		return list;
	}

	// Return list of string values from method (typical for using in ComboEdit)
	ListOfStrings listOfStrings(DataMethodReturningString method) const
	{
		ListOfStrings list;
		for (const auto& data : _data_list) {
			list.insert((data.*method)());
		}
		return list;
	}

	// Return numbers of items with the same string values of method (typical for using in WidgetChart)
	NumbersByStrings numbersByStrings(DataMethodReturningString method) const
	{
		NumbersByStrings list;
		for (const auto& data : _data_list) {
			++list[(data.*method)()];
		}
		return list;
	}

	// Return numbers of items with the same integer values of method (typical for using in WidgetChart)
	NumbersByIntegers numbersByIntegers(DataMethodReturningInteger method) const
	{
		NumbersByIntegers list;
		for (const auto& data : _data_list) {
			++list[(data.*method)()];
		}
		return list;
	}

	// Return map of <method_key, method_val> integer values (typical for using in WidgetChart)
	NumbersByIntegers numbersByIntegers(DataMethodReturningInteger method_key,
										DataMethodReturningInteger method_val) const
	{
		NumbersByIntegers list;
		for (const auto& data : _data_list) {
			list[(data.*method_key)()] = (data.*method_val)();
		}
		return list;
	}

	enum class RangeTypes
	{
		Discrete,
		Linear,
		LinearWithMin,
		LinearWithMax,
	};
	// Standard helper for functions, whose need to count
	// number of items in _data_list by some criteria
	// and return in container like a std::map<QString, uint32_t>
	// funcIn - lambda for extraction required member of data (must return uint32_t)
	// funcOut - lambda for creating key for list (must return QString)
	template<typename FuncIn, typename FuncOut>
	NumbersByStrings numbersInRange(uint32_t step,
			RangeTypes range_type, uint32_t required_min, uint32_t required_max,
			FuncIn&& funcIn, FuncOut&& funcOut) const
	{
		NumbersByStrings list;
		uint32_t real_min = Global::undefined_value, real_max = Global::undefined_value;
		for (const auto& data : _data_list) {
			auto val = funcIn(data);
			Helper::checkMinMax(val, &real_min, &real_max);
			if ((range_type == RangeTypes::LinearWithMin) && (val < required_min)) {
				++list[QStringLiteral("&lt;%1").arg(required_min)];
			} else if ((range_type == RangeTypes::LinearWithMax) && (val >= required_max)) {
				++list[QStringLiteral("%1+").arg(required_max)];
			} else {
				++list[funcOut(val, step)];
			}
		}
		if (range_type != RangeTypes::Discrete) {
			if (range_type == RangeTypes::LinearWithMin) { real_min = required_min; }
			if (range_type == RangeTypes::LinearWithMax) { real_max = required_max; }
			real_min = (real_min / step) * step;
			real_max = (real_max / step) * step;
			for (uint32_t val = real_min; val < real_max; val += step) {
				list.try_emplace(funcOut(val, step), 0);
			}
		}
		return list;
	}

protected:
	ListContainer _data_list;
};

} // namespace Base
