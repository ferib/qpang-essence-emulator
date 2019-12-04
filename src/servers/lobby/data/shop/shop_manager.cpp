#include "shop_manager.hpp"

ShopManager::ShopManager()
{
	Load();
}

ShopManager::~ShopManager()
{

}

void ShopManager::Load()
{
	_items.clear();

	Database database{};
	auto result = database.storeQuery("SELECT * FROM items WHERE status > 0 AND seq_id > 0");
	
	if (result)
	{
		sLogger->Get()->info("Loading shop items");
		do
		{
			std::string name = result->getString("name");
			uint32_t sequenceId = result->getNumber<uint32_t>("seq_id");
			uint32_t itemId = result->getNumber<uint32_t>("item_id");
			uint8_t itemType = result->getNumber<uint32_t>("type");
			uint8_t payType = result->getNumber<uint32_t>("pay_type");
			uint32_t price = result->getNumber<uint32_t>("price");
			uint8_t useType = result->getNumber<uint32_t>("use_up");
			uint16_t period = result->getNumber<uint32_t>("period");
			uint8_t minLevel = result->getNumber<uint32_t>("level");
			uint8_t state = result->getNumber<uint32_t>("status");
			uint16_t soldCount = result->getNumber<uint32_t>("sold_count");;
			uint16_t stock = result->getNumber<uint32_t>("stock");
			_items.push_back(ShopItem{ name, sequenceId, itemId, itemType, payType, price, useType, period, minLevel, state, soldCount, stock });

			if (_items.size() >= 2460)
			{
				sLogger->Get()->warn("Maximum shop items reached: {0:d}", _items.size());
				break;
			}

			result->next();
		} while (result->hasNext());
		sLogger->Get()->info("{0:d} items were loaded", _items.size());
	}
	else
		sLogger->Get()->error("No shop items were loaded");

	database.Close();
}

std::vector<ShopItem> ShopManager::List()
{
	return _items;
}

ShopItem ShopManager::GetItemByItemId(uint32_t itemId)
{
	for (ShopItem item : _items)
		if (item.itemId == itemId)
			return item;

	return *_items.begin();
}

InventoryCard ShopManager::Buy(ShopItem item, uint32_t playerId)
{
	sLogger->Get()->info("Shopmanager: {0:d} bought item with id: {1:d}", playerId, item.itemId);
	return InventoryCard{ playerId, 0, item.itemId, item.period, item.useType, item.itemType, 1, 1, 0, 0, (uint32_t)time(NULL) };
}

ShopItem ShopManager::GetItemBySequenceId(uint32_t seqId)
{
	for (ShopItem item : _items)
		if (item.sequenceId == seqId)
			return item;

	return *_items.begin();
}