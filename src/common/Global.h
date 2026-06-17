#pragma once

#include <QColor>

#include <cstdint>

namespace Global
{
	const uint32_t undefined_value = 0;

	namespace Colors
	{
		const QColor tree_level_1 = QColor(240, 240, 240);
		const QColor tree_level_2 = QColor(230, 230, 230);
		const QColor tree_level_3 = QColor(220, 220, 220);

		const QColor rating[10] =
		{
			QColor(255, 100, 100), // 1
			QColor(250, 150, 150), // 2
			QColor(245, 190, 190), // 3
			QColor(240, 220, 220), // 4
			QColor(235, 235, 235), // 5
			QColor(210, 240, 210), // 6
			QColor(180, 245, 180), // 7
			QColor(150, 250, 150), // 8
			QColor(100, 255, 100), // 9
			QColor( 50, 255,  50), // 10
		};
	}
} // namespace Global
