#pragma once

#include "BaseData.h"

#include <QString>

namespace Base
{

class Extra : public Data
{
public:
	Extra() = default;

	void clear()
	{ *this = Extra(); }

	inline QString id() const override
	{ return group() + title(); }

	template<typename T>
	inline void setGroup(T&& group)
	{ _group = std::forward<T>(group); }
	inline QString group() const
	{ return _group; }

	template<typename T>
	inline void setTitle(T&& title)
	{ _title = std::forward<T>(title); }
	inline QString title() const
	{ return _title; }

	template<typename T>
	inline void setNotes(T&& notes)
	{ _notes = std::forward<T>(notes); }
	inline QString notes() const
	{ return _notes; }

	bool operator==(const Extra& other) const noexcept = default;

private:
	QString _group;
	QString _title;
	QString _notes;
};

} // namespace Base
