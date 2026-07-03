#pragma once

#include "Global.h"

#include <QString>
#include <QCoreApplication>

namespace Helper
{
	inline QString stdPath(const QString& file_name)
	{
		return QCoreApplication::applicationDirPath() + '/' + file_name;
	}
	inline QString stdPathSettings()
	{
		return stdPath(Global::settings_file_name);
	}

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

	inline std::pair<uint32_t, uint32_t> initMinMax()
	{
		return {Global::undefined_value, Global::undefined_value};
	}
	inline void checkMinMax(uint32_t val, uint32_t* min, uint32_t* max)
	{
		if (val != Global::undefined_value) {
			if ((*min > val) || (*min == Global::undefined_value)) { *min = val; }
			if ((*max < val) || (*max == Global::undefined_value)) { *max = val; }
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
				(min_year == max_year) ?
				QStringLiteral("%1").arg(min_year, 4, 10, QChar('0')) :
				QStringLiteral("%1-%2")
					.arg(min_year, 4, 10, QChar('0'))
					.arg(max_year, 4, 10, QChar('0'));
	}
	inline QString yearString(std::pair<uint32_t, uint32_t> min_max_year)
	{
		return yearString(min_max_year.first, min_max_year.second);
	}
	inline QString yearString(uint32_t year)
	{
		return	(year == Global::undefined_value) ?
				QStringLiteral() :
				QStringLiteral("%1").arg(year, 4, 10, QChar('0'));
	}

	inline QString epochString(uint32_t year, uint32_t step)
	{
		if (step == 1) {
			return	(year == Global::undefined_value) ?
					QStringLiteral("[Неизвестный]") :
					QStringLiteral("%1").arg(year, 4, 10, QChar('0'));
		} else {
			return	(year == Global::undefined_value) ?
					QStringLiteral("[Неизвестное]") :
					QStringLiteral("%1-е").arg((year / step) * step, 4, 10, QChar('0'));
		}
	}

	inline QColor ratingColor(uint32_t rating)
	{
		return Global::Colors::rating[((1 <= rating) && (rating <= 10)) ? rating-1 : 4];
	}
} // namespace Helper
