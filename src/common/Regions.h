#pragma once

#include <QStringList>

#include <unordered_map>

class Regions
{
public:
	Regions() = delete;

	static void init();

	static QStringList get(const QString& country);
	static QStringList get(const QStringList& countries);

private:
	inline static std::unordered_map<QString, QStringList> _country_to_region;

	enum Columns
	{
		CLMN_COUNTRY,
		CLMN_REGIONS,
		NUM_OF_COLUMNS
	};
};

