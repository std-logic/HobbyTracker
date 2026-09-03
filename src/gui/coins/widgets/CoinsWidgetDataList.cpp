#include "CoinsWidgetDataList.h"
#include "../common/CoinsCommon.h"
#include "../data/CoinsDataList.h"

#include <gui/base/data/BaseExtraList.h>
#include <gui/base/widgets/BaseWidgetTreeItem.h>

#include <common/Regions.h>

Coins::WidgetDataList::WidgetDataList(QWidget* parent)
	: Base::WidgetTree{parent}
{
}

void Coins::WidgetDataList::update(const DataList& data_list, const Base::ExtraList& extra_list)
{
	clear();
	setRootIsDecorated(static_cast<DataListViewModes>(_view_mode) != DataListViewModes::Simple);
	switch (static_cast<DataListViewModes>(_view_mode)) {
		case DataListViewModes::ByCountries:	showByCountries(data_list, extra_list);		break;
		case DataListViewModes::ByRegions:		showByRegions(data_list, extra_list);		break;
		case DataListViewModes::ByDecades:		showByDecades(data_list);					break;
		case DataListViewModes::ByCenturies:	showByCenturies(data_list);					break;
		case DataListViewModes::Simple:			showSimple(data_list);						break;
		default: return;
	}
}

void Coins::WidgetDataList::showByCountries(const DataList& data_list, const Base::ExtraList& extra_list)
{
	enum Columns {CLMN_COUNTRY, CLMN_COUNT, CLMN_VALUE, CLMN_TITLE,
				  CLMN_DIAMETER, CLMN_NUMBER, CLMN_YEAR, CLMN_VERSION, CLMN_STATE};
	initColumns({tr("Страна / Период / Валюта"), tr("К-во"), tr("Номинал"), tr("Название"),
				 tr("D, мм"), tr("Номер"), tr("Год"), tr("Разн."), tr("Сост.")},
				{WIDTH_COUNTRY_BIG, WIDTH_COUNT, WIDTH_VALUE, WIDTH_TITLE,
				 WIDTH_DIAMETER, WIDTH_NUMBER, WIDTH_YEAR, WIDTH_VERSION, WIDTH_STATE});
	initSorting(CLMN_COUNTRY);

	auto synonyms = extra_list.getSynonyms(tr("[Синонимы для стран]"));
	auto coins_by_countries = data_list.coinsByCountries(synonyms);

	for (const auto& [country, coins_by_periods] : coins_by_countries) {
		auto item_country = new Base::WidgetTreeItem(this, Global::Colors::tree_level_2);
		item_country->setCountry(CLMN_COUNTRY, country);
		uint32_t country_coins_num = 0;
		uint32_t country_min_year = Global::undefined_value;
		uint32_t country_max_year = Global::undefined_value;

		for (const auto& [period, coins] : coins_by_periods) {
			auto item_period = new Base::WidgetTreeItem(item_country, Global::Colors::tree_level_1);
			item_period->setText(CLMN_COUNTRY, period);
			item_period->setNumb(CLMN_COUNT, coins.size());
			item_period->setText(CLMN_YEAR, Helper::yearString(coins));
			country_coins_num += coins.size();

			for (const auto coin : coins) {
				auto item_coin = new Base::WidgetTreeItem(item_period);
				item_coin->setText(CLMN_COUNTRY, coin->currency());
				item_coin->setText(CLMN_VALUE, coin->value());
				item_coin->setText(CLMN_TITLE, coin->title());
				item_coin->setText(CLMN_DIAMETER, coin->diameter());
				item_coin->setText(CLMN_NUMBER, coin->number());
				item_coin->setText(CLMN_YEAR, coin->yearString());
				item_coin->setText(CLMN_VERSION, coin->version());
				item_coin->setText(CLMN_STATE, coin->state());
				item_coin->setToolTipEverywhere(coin->summaryString());
				item_coin->setId(coin->id());
				Helper::checkMinMax(coin->year(), &country_min_year, &country_max_year);
			}
		}

		item_country->setNumb(CLMN_COUNT, country_coins_num);
		item_country->setText(CLMN_YEAR, Helper::yearString(country_min_year, country_max_year));
	}
}

void Coins::WidgetDataList::showByRegions(const DataList& data_list, const Base::ExtraList& extra_list)
{
	enum Columns {CLMN_COUNTRY, CLMN_COUNT, CLMN_VALUE, CLMN_TITLE,
				  CLMN_DIAMETER, CLMN_NUMBER, CLMN_YEAR, CLMN_VERSION, CLMN_STATE};
	initColumns({tr("Регион / Страна / Период / Валюта"), tr("К-во"), tr("Номинал"), tr("Название"),
				 tr("D, мм"), tr("Номер"), tr("Год"), tr("Разн."), tr("Сост.")},
				{WIDTH_COUNTRY_BIG, WIDTH_COUNT, WIDTH_VALUE, WIDTH_TITLE,
				 WIDTH_DIAMETER, WIDTH_NUMBER, WIDTH_YEAR, WIDTH_VERSION, WIDTH_STATE});
	initSorting(CLMN_COUNTRY);

	auto synonyms = extra_list.getSynonyms(tr("[Синонимы для стран]"));
	auto coins_by_regions = data_list.coinsByRegions(synonyms);

	for (const auto& [region, coins_by_countries] : coins_by_regions) {
		auto item_region = new Base::WidgetTreeItem(this, Global::Colors::tree_level_3);
		item_region->setText(CLMN_COUNTRY, region);
		uint32_t region_coins_num = 0;
		uint32_t region_min_year = Global::undefined_value;
		uint32_t region_max_year = Global::undefined_value;
		std::unordered_set<QString> present_countries;

		for (const auto& [country, coins_by_periods] : coins_by_countries) {
			auto item_country = new Base::WidgetTreeItem(item_region, Global::Colors::tree_level_2);
			item_country->setCountry(CLMN_COUNTRY, country);
			uint32_t country_coins_num = 0;
			uint32_t country_min_year = Global::undefined_value;
			uint32_t country_max_year = Global::undefined_value;
			present_countries.insert(country);

			for (const auto& [period, coins] : coins_by_periods) {
				auto item_period = new Base::WidgetTreeItem(item_country, Global::Colors::tree_level_1);
				item_period->setText(CLMN_COUNTRY, period);
				item_period->setNumb(CLMN_COUNT, coins.size());
				item_period->setText(CLMN_YEAR, Helper::yearString(coins));
				country_coins_num += coins.size();

				for (const auto coin : coins) {
					auto item_coin = new Base::WidgetTreeItem(item_period);
					item_coin->setText(CLMN_COUNTRY, coin->currency());
					item_coin->setText(CLMN_VALUE, coin->value());
					item_coin->setText(CLMN_TITLE, coin->title());
					item_coin->setText(CLMN_DIAMETER, coin->diameter());
					item_coin->setText(CLMN_NUMBER, coin->number());
					item_coin->setText(CLMN_YEAR, coin->yearString());
					item_coin->setText(CLMN_VERSION, coin->version());
					item_coin->setText(CLMN_STATE, coin->state());
					item_coin->setToolTipEverywhere(coin->summaryString());
					item_coin->setId(coin->id());
					Helper::checkMinMax(coin->year(), &country_min_year, &country_max_year);
				}
			}

			item_country->setNumb(CLMN_COUNT, country_coins_num);
			item_country->setText(CLMN_YEAR, Helper::yearString(country_min_year, country_max_year));
			region_coins_num += country_coins_num;
			Helper::checkMin(country_min_year, &region_min_year);
			Helper::checkMax(country_max_year, &region_max_year);
		}

		item_region->setNumb(CLMN_COUNT, region_coins_num);
		item_region->setText(CLMN_YEAR, Helper::yearString(region_min_year, region_max_year));
		item_region->setToolTipEverywhere(Regions::progress(region, present_countries));
	}
}

void Coins::WidgetDataList::showByDecades(const DataList& data_list)
{
	enum Columns {CLMN_COUNTRY, CLMN_COUNT, CLMN_PERIOD, CLMN_CURRENCY,
				  CLMN_VALUE, CLMN_TITLE, CLMN_DIAMETER, CLMN_NUMBER,
				  CLMN_YEAR, CLMN_VERSION, CLMN_STATE};
	initColumns({tr("Десятилетие / Страна"), tr("К-во"), tr("Период"), tr("Валюта"),
				 tr("Номинал"), tr("Название"), tr("D, мм"), tr("Номер"),
				 tr("Год"), tr("Разн."), tr("Сост.")},
				{WIDTH_COUNTRY_SMALL, WIDTH_COUNT, WIDTH_PERIOD, WIDTH_CURRENCY,
				 WIDTH_VALUE, WIDTH_TITLE, WIDTH_DIAMETER, WIDTH_NUMBER,
				 WIDTH_YEAR, WIDTH_VERSION, WIDTH_STATE});
	initSorting(CLMN_COUNTRY);

	auto coins_by_decades = data_list.coinsByYears(10);

	for (const auto& [decade, coins] : coins_by_decades) {
		auto item_decade = new Base::WidgetTreeItem(this, Global::Colors::tree_level_1);
		item_decade->setText(CLMN_COUNTRY, decade);
		item_decade->setNumb(CLMN_COUNT, coins.size());
		item_decade->setText(CLMN_YEAR, Helper::yearString(coins));

		for (const auto coin : coins) {
			auto item_coin = new Base::WidgetTreeItem(item_decade);
			item_coin->setText(CLMN_COUNTRY, coin->country());
			item_coin->setText(CLMN_PERIOD, coin->period());
			item_coin->setText(CLMN_CURRENCY, coin->currency());
			item_coin->setText(CLMN_VALUE, coin->value());
			item_coin->setText(CLMN_TITLE, coin->title());
			item_coin->setText(CLMN_DIAMETER, coin->diameter());
			item_coin->setText(CLMN_NUMBER, coin->number());
			item_coin->setText(CLMN_YEAR, coin->yearString());
			item_coin->setText(CLMN_VERSION, coin->version());
			item_coin->setText(CLMN_STATE, coin->state());
			item_coin->setToolTipEverywhere(coin->summaryString());
			item_coin->setId(coin->id());
		}
	}
}

void Coins::WidgetDataList::showByCenturies(const DataList& data_list)
{
	enum Columns {CLMN_COUNTRY, CLMN_COUNT, CLMN_PERIOD, CLMN_CURRENCY,
				  CLMN_VALUE, CLMN_TITLE, CLMN_DIAMETER, CLMN_NUMBER,
				  CLMN_YEAR, CLMN_VERSION, CLMN_STATE};
	initColumns({tr("Столетие / Страна"), tr("К-во"), tr("Период"), tr("Валюта"),
				 tr("Номинал"), tr("Название"), tr("D, мм"), tr("Номер"),
				 tr("Год"), tr("Разн."), tr("Сост.")},
				{WIDTH_COUNTRY_SMALL, WIDTH_COUNT, WIDTH_PERIOD, WIDTH_CURRENCY,
				 WIDTH_VALUE, WIDTH_TITLE, WIDTH_DIAMETER, WIDTH_NUMBER,
				 WIDTH_YEAR, WIDTH_VERSION, WIDTH_STATE});
	initSorting(CLMN_COUNTRY);

	auto coins_by_centuries = data_list.coinsByYears(100);

	for (const auto& [century, coins] : coins_by_centuries) {
		auto item_century = new Base::WidgetTreeItem(this, Global::Colors::tree_level_1);
		item_century->setNumb(CLMN_COUNTRY, century);
		item_century->setNumb(CLMN_COUNT, coins.size());
		item_century->setText(CLMN_YEAR, Helper::yearString(coins));

		for (const auto coin : coins) {
			auto item_coin = new Base::WidgetTreeItem(item_century);
			item_coin->setText(CLMN_COUNTRY, coin->country());
			item_coin->setText(CLMN_PERIOD, coin->period());
			item_coin->setText(CLMN_CURRENCY, coin->currency());
			item_coin->setText(CLMN_VALUE, coin->value());
			item_coin->setText(CLMN_TITLE, coin->title());
			item_coin->setText(CLMN_DIAMETER, coin->diameter());
			item_coin->setText(CLMN_NUMBER, coin->number());
			item_coin->setText(CLMN_YEAR, coin->yearString());
			item_coin->setText(CLMN_VERSION, coin->version());
			item_coin->setText(CLMN_STATE, coin->state());
			item_coin->setToolTipEverywhere(coin->summaryString());
			item_coin->setId(coin->id());
		}
	}
}

void Coins::WidgetDataList::showSimple(const DataList& data_list)
{
	enum Columns {CLMN_COUNTRY, CLMN_PERIOD, CLMN_CURRENCY, CLMN_VALUE, CLMN_TITLE,
				  CLMN_DIAMETER, CLMN_NUMBER, CLMN_YEAR, CLMN_VERSION, CLMN_STATE};
	initColumns({tr("Страна"), tr("Период"), tr("Валюта"), tr("Номинал"), tr("Название"),
				 tr("D, мм"), tr("Номер"), tr("Год"), tr("Разн."), tr("Сост.")},
				{WIDTH_COUNTRY_SMALL, WIDTH_PERIOD, WIDTH_CURRENCY, WIDTH_VALUE, WIDTH_TITLE,
				 WIDTH_DIAMETER, WIDTH_NUMBER, WIDTH_YEAR, WIDTH_VERSION, WIDTH_STATE});
	initSorting(CLMN_COUNTRY);

	for (const auto& coin : data_list) {
		auto item_coin = new Base::WidgetTreeItem(this);
		item_coin->setText(CLMN_COUNTRY, coin.country());
		item_coin->setText(CLMN_PERIOD, coin.period());
		item_coin->setText(CLMN_CURRENCY, coin.currency());
		item_coin->setText(CLMN_VALUE, coin.value());
		item_coin->setText(CLMN_TITLE, coin.title());
		item_coin->setText(CLMN_DIAMETER, coin.diameter());
		item_coin->setText(CLMN_NUMBER, coin.number());
		item_coin->setText(CLMN_YEAR, coin.yearString());
		item_coin->setText(CLMN_VERSION, coin.version());
		item_coin->setText(CLMN_STATE, coin.state());
		item_coin->setToolTipEverywhere(coin.summaryString());
		item_coin->setId(coin.id());
	}
}
