#pragma once

#include <QColor>
#include <QMargins>

#include <cstdint>

namespace Global
{
	inline const char settings_file_name[] = "HobbyTrackerSettings.ini";

	inline const uint32_t undefined_value = 0;

	namespace Colors
	{
		inline const QColor tree_level_1 = QColor(210, 210, 210);
		inline const QColor tree_level_2 = QColor(200, 200, 200);
		inline const QColor tree_level_3 = QColor(190, 190, 190);

		inline const QColor rating[10] =
		{
			QColor(255, 100, 100), // 1
			QColor(250, 150, 150), // 2
			QColor(245, 190, 190), // 3
			QColor(240, 220, 220), // 4
			QColor(235, 235, 235), // 5
			QColor(205, 240, 210), // 6
			QColor(180, 245, 190), // 7
			QColor(140, 250, 160), // 8
			QColor( 90, 255, 110), // 9
			QColor( 30, 255,  50), // 10
		};
	} // namespace Colors

	namespace Stylesheets
	{
		inline const char label_value[] =
				"QLabel{"
				"background-color: rgb(240,240,240); "
				"border: 1px solid rgb(200,200,200); "
				"border-radius: 6px;"
				"padding-left: 10px;"
				"padding-right: 10px;"
				"}";
		inline const char tree_widget[] =
				"QTreeWidget{"
				"background-color: rgb(230,230,230);"
				"color: black;"
				"}";
		inline const char button_highligh[] =
				"QPushButton{"
				"background-color: rgb(140,250,160);"
				"}";
	} // namespace Stylesheets

	namespace Sizes
	{
		inline const int window_min_width = 960;
		inline const int window_min_height = 540;

		inline const int font_small = 9;
		inline const int font_big = 11;

		inline const int default_spacing = 5;
		inline const QMargins default_margin = {5, 5, 5, 5};
	} // namespace Sizes

} // namespace Global
