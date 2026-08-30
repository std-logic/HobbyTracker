#pragma once

#include <QStringList>
#include <QCoreApplication>

#include <unordered_map>
#include <set>

class Regions
{
	Q_DECLARE_TR_FUNCTIONS(Regions)
public:
	Regions() = delete;

	struct CountryData
	{
		QString region;
		bool is_former = false;
		bool is_union = false;
	};

	static void init();

	static QString get(const QString& country);
	static QStringList get(const QStringList& countries);

	static QStringList missingCountries(const QString& region,
			const std::set<QString>& present_countries);
	static QString progress(const QString& region,
			const std::set<QString>& present_countries);

private:
	inline static std::unordered_map<QString, CountryData> _country_data;
	inline static std::unordered_map<QString, std::set<QString>> _region_countries;

	enum Columns
	{
		CLMN_COUNTRY,
		CLMN_REGIONS,
		CLMN_FORMER,
		CLMN_UNION,
		NUM_OF_COLUMNS
	};
};

