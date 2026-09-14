#pragma once

#include <gui/base/widgets/BaseWidgetTree.h>

namespace Base
{
class ExtraList;
}

namespace Concerts
{

class DataList;

class WidgetDataList : public Base::WidgetTree
{
	Q_OBJECT
public:
	explicit WidgetDataList(QWidget* parent = nullptr);
	~WidgetDataList() = default;

	void update(const DataList& data_list, const Base::ExtraList& extra_list, const QString& photo_dir);

public slots:
	void setFavoritesState(Qt::CheckState state);

signals:

private:
	void showByYears(const DataList& data_list, const QString& photo_dir);
	void showByArtists(const DataList& data_list, const Base::ExtraList& extra_list, const QString& photo_dir);
	void showByTags(const DataList& data_list, const Base::ExtraList& extra_list, const QString& photo_dir);
	void showByCountries(const DataList& data_list, const QString& photo_dir);
	void showByCities(const DataList& data_list, const QString& photo_dir);
	void showByPlaces(const DataList& data_list, const Base::ExtraList& extra_list, const QString& photo_dir);
	void showPlacesTree(const DataList& data_list, const Base::ExtraList& extra_list, const QString& photo_dir);
	void showSimple(const DataList& data_list, const QString& photo_dir);

private:
	static const int WIDTH_DATE_SMALL = 150;
	static const int WIDTH_DATE_MEDIUM = 280;
	static const int WIDTH_DATE_BIG = 400;
	static const int WIDTH_COUNT = 50;
	static const int WIDTH_ARTISTS = 0; // stretched
	static const int WIDTH_COUNTRY = 120;
	static const int WIDTH_CITY = 170;
	static const int WIDTH_PLACE = 260;
	static const int WIDTH_PHOTOS = 30;

	bool _favorites_state = false;
};

} // namespace Concerts
