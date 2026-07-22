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

	inline QString stringListToString(const QStringList& str_list, const QString& delimiter)
	{
		QString str;
		for (int i = 0; i < str_list.size(); ++i) {
			str += str_list[i];
			if (i != (str_list.size() - 1)) {
				str += delimiter;
			}
		}
		return str;
	}

	inline void checkMinMax(uint32_t val, uint32_t* min, uint32_t* max)
	{
		if (val != Global::undefined_value) {
			if ((*min > val) || (*min == Global::undefined_value)) { *min = val; }
			if ((*max < val) || (*max == Global::undefined_value)) { *max = val; }
		}
	}

	inline void checkMinMaxAny(uint32_t val, uint32_t* min, uint32_t* max)
	{
		if (*min > val) { *min = val; }
		if (*max < val) { *max = val; }
	}

	inline void checkMin(uint32_t val, uint32_t* min)
	{
		if (val != Global::undefined_value) {
			if ((*min > val) || (*min == Global::undefined_value)) { *min = val; }
		}
	}

	inline void checkMax(uint32_t val, uint32_t* max)
	{
		if (val != Global::undefined_value) {
			if ((*max < val) || (*max == Global::undefined_value)) { *max = val; }
		}
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

	template<typename T>
	concept has_year_func = requires(T a) { a.year(); };
	template<has_year_func T>
	inline QString yearString(std::vector<const T*> list)
	{
		uint32_t min_year = Global::undefined_value, max_year = Global::undefined_value;
		for (auto data : list) {
			checkMinMax(data->year(), &min_year, &max_year);
		}
		return yearString(min_year, max_year);
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
					QStringLiteral("Неизвестные") :
					QStringLiteral("%1").arg(year, 4, 10, QChar('0'));
		} else {
			return	(year == Global::undefined_value) ?
					QStringLiteral("Неизвестные") :
					QStringLiteral("%1-е").arg((year / step) * step, 4, 10, QChar('0'));
		}
	}

	inline QString sizeString(uint64_t size)
	{
		return	(size <= 1024 * 1024 * 1024) ?
				QStringLiteral("%1 МБ").arg(static_cast<double>(size) / (1024. * 1024.), 0, 'f', 0) :
				QStringLiteral("%1 ГБ").arg(static_cast<double>(size) / (1024. * 1024. * 1024.), 0, 'f', 2);
	}

	inline QString timeString(uint32_t time)
	{
		return	(time < 60 * 60000) ?
				QStringLiteral("%1:%2")
					.arg(time / 60000)
					.arg((time % 60000) / 1000, 2, 10, QChar('0')) :
				QStringLiteral("%1:%2:%3")
					.arg(time / (60 * 60000))
					.arg((time % (60 * 60000)) / 60000, 2, 10, QChar('0'))
					.arg((time % 60000) / 1000, 2, 10, QChar('0'));
	}

	inline QColor ratingColor(uint32_t rating)
	{
		return Global::Colors::rating[((1 <= rating) && (rating <= 10)) ? rating-1 : 4];
	}
} // namespace Helper
