#pragma once

#include "Global.h"

#include <QString>

namespace Helper
{
	inline QString fullTrAndOrigString(const QString& tr_str, const QString& orig_str)
	{
		if (tr_str.isEmpty()) {
			return orig_str;
		} else if (orig_str.isEmpty()) {
			return tr_str;
		} else {
			return QStringLiteral("%1 (%2)").arg(tr_str, orig_str);
		}
	}

	inline auto checkMinYear(uint32_t curr_min_year, uint32_t year)
	{
		if (year != Global::undefined_value) {
			if ((curr_min_year > year) || (curr_min_year == Global::undefined_value)) {
				curr_min_year = year;
			}
		}
		return curr_min_year;
	}
	inline auto checkMaxYear(uint32_t curr_max_year, uint32_t year)
	{
		if (year != Global::undefined_value) {
			if ((curr_max_year < year) || (curr_max_year == Global::undefined_value)) {
				curr_max_year = year;
			}
		}
		return curr_max_year;
	}
	inline QString yearString(uint32_t min_year, uint32_t max_year)
	{
		return	(min_year == Global::undefined_value) ? QString() :
				(min_year == max_year) ? QString::number(min_year) :
				QStringLiteral("%1-%2").arg(min_year).arg(max_year);
	}
	inline QString yearString(std::pair<uint32_t, uint32_t> min_max_year)
	{
		return yearString(min_max_year.first, min_max_year.second);
	}

	inline QString epochString(uint32_t year, uint32_t step)
	{
		return	(year == Global::undefined_value) ?
				QStringLiteral("[Неизвестное]") :
				QStringLiteral("%1-е").arg((year / step) * step);
	}
}
