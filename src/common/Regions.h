#pragma once

#include <QIcon>
#include <QStringList>
#include <QCoreApplication>

#include <unordered_map>
#include <unordered_set>
#include <map>
#include <set>

class Regions
{
	Q_DECLARE_TR_FUNCTIONS(Regions)
public:
	Regions() = delete;

	struct CountryData
	{
		QString code;
		QString region;
		QString comment;
		QIcon icon;
		bool is_former = false;
		bool is_union = false;
	};

	static void init();

	static CountryData data(const QString& country);

	static QIcon icon(const QString& country);

	static QString region(const QString& country);
	static QStringList region(const QStringList& countries);

	static QString comment(const QString& country);

	static bool isFormer(const QString& country);
	static bool isUnion(const QString& country);

	static QStringList missingCountries(const QString& region,
			const std::unordered_set<QString>& present_countries);

	static QString progress(const QString& region,
			const std::unordered_set<QString>& present_countries);
	static QString progress(const std::unordered_set<QString>& present_countries);

private:
	inline static std::unordered_map<QString, CountryData> _country_data;
	inline static std::map<QString, std::set<QString>> _region_countries;
	inline static int _countries_total_num = 0;

	enum Columns
	{
		CLMN_COUNTRY,
		CLMN_CODE,
		CLMN_REGIONS,
		CLMN_FORMER,
		CLMN_UNION,
		CLMN_COMMENT,
		NUM_OF_COLUMNS
	};
};
