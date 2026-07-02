#pragma once

#include <common/Helper.h>

#include <cstdint>
#include <vector>
#include <set>

namespace Base
{

template <typename T>
class DataList
{
public:
	DataList() = default;
	virtual ~DataList() = default;

	using ListContainer = std::vector<T>;
	using SubListContainer = std::vector<const T*>;
	using ListOfStrings = std::set<QString>;

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

	inline void add(const T& data)
	{ _data_list.push_back(data); }

	using NumbersInRange = std::map<QString, uint32_t>;
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
	NumbersInRange numbersInRange(uint32_t step,
			RangeTypes range_type, uint32_t required_min, uint32_t required_max,
			FuncIn&& funcIn, FuncOut&& funcOut) const
	{
		NumbersInRange list;
		auto [real_min, real_max] = Helper::initMinMax();
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
