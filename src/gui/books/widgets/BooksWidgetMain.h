#pragma once

#include "../data/BooksDataList.h"
#include "../data/BooksSettings.h"

#include <storage/csv/CsvData.h>
#include <gui/base/widgets/BaseWidgetMain.h>

namespace Books
{

class WidgetControl;
class WidgetList;
class WidgetStatistics;

class WidgetMain : public Base::WidgetMain
{
	Q_OBJECT
public:
	explicit WidgetMain(QWidget* parent = nullptr);
	~WidgetMain() = default;

	static QString getName() { return tr("Литература"); };

	void start() override;

	void dataCsv(const Csv::Settings& csv_settings, const Csv::Data& csv_data);

signals:
	void readCsv(const Csv::Settings& csv_settings);

private:
	void initGui();
	void initConnections();

private slots:
	void updateList();

private:
	WidgetControl* _control = nullptr;
	WidgetList* _list = nullptr;
	WidgetStatistics* _statistics = nullptr;

	std::optional<Csv::Data> _csv_data;
	std::optional<DataList> _data_list;
	Settings _settings;
};

} // namespace Books
