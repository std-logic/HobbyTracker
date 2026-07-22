#pragma once

#include <gui/base/widgets/BaseWidgetSummary.h>

class QLabel;

namespace Player
{

class Library;

class WidgetSummary : public Base::WidgetSummary
{
	Q_OBJECT
public:
	explicit WidgetSummary(QWidget* parent = nullptr);
	~WidgetSummary() = default;

	void update(const Library& library);
	void update(const std::vector<Library>& libraries);

private:
	void initWidgets();

private:
	QLabel* _label_title = nullptr;
	QLabel* _label_years = nullptr;
	QLabel* _label_artists_num = nullptr;
	QLabel* _label_albums_num = nullptr;
	QLabel* _label_tracks_num = nullptr;
	QLabel* _label_play_count = nullptr;
	QLabel* _label_genres_num = nullptr;
};

} // namespace Player
