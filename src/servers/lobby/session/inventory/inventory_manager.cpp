#include "inventory_manager.hpp"
#include <boost/format.hpp>

InventoryManager::InventoryManager()
{

}

InventoryManager::~InventoryManager()
{

}

void InventoryManager::Load(uint32_t playerId)
{
	Database database{};
	auto result = database.storeQuery(str(boost::format("SELECT * FROM player_items WHERE player_id = %1% ORDER BY time DESC") % playerId));
	if (result != nullptr)
	{
		do
		{
			uint32_t ownerId = result->getNumber<uint32_t>("player_id");
			uint32_t id = result->getNumber<uint32_t>("id");
			uint32_t itemId = result->getNumber<uint32_t>("item_id");
			uint16_t period = result->getNumber<uint32_t>("period");
			uint8_t periodType = result->getNumber<uint32_t>("period_type");
			uint8_t itemType = result->getNumber<uint32_t>("type");
			uint8_t opened = result->getNumber<uint32_t>("opened");
			uint8_t giftable = result->getNumber<uint32_t>("giftable");
			uint8_t boostLevel = result->getNumber<uint32_t>("boost_level");
			uint8_t boosted = result->getNumber<uint32_t>("boosted");
			uint32_t timeCreated = result->getNumber<uint32_t>("time");
			_items.push_back(InventoryCard{ ownerId, id, itemId, period, periodType, itemType, opened, giftable, boostLevel, boosted, timeCreated });
			result->next();

			if (_items.size() >= MAX_INVENTORY)
				break;
		} while (result->hasNext());
	}
	database.Close();
}

std::vector<InventoryCard> InventoryManager::List()
{
	return _items;
}

InventoryCard InventoryManager::GetItemByCardId(uint32_t cardId)
{
	for (InventoryCard card : _items)
		if (card.id == cardId)
			return card;

	return InventoryCard{};
}

bool InventoryManager::RemoveItem(uint32_t cardId)
{
	InventoryCard card = GetItemByCardId(cardId);

	for (auto it = _items.begin(); it != _items.end(); it++)
	{
		if ((*it).id == card.id)
		{
			_items.erase(it);

			Database database{};
			database.executeQuery(str(boost::format("DELETE FROM player_items WHERE id = %1%") % cardId));
			database.Close();

			return true;
		}
	}

	return false;
}

InventoryCard InventoryManager::AddItem(InventoryCard card)
{
	if (_items.size() >= MAX_INVENTORY)
		return InventoryCard{};

	Database database{};
	bool result = database.executeQuery(
		"INSERT INTO player_items (player_id, item_id, period, period_type, type, opened, giftable, boost_level, boosted, time) VALUES "
		"("
		"" + std::to_string(card.ownerId) + ","
		"" + std::to_string(card.itemId) + ","
		"" + std::to_string(card.period) + ","
		"" + std::to_string(card.periodType) + ","
		"" + std::to_string(card.itemType) + ","
		"" + std::to_string(card.opened) + ","
		"" + std::to_string(card.giftable) + ","
		"" + std::to_string(card.boostLevel) + ","
		"" + std::to_string(card.boosted) + ","
		"" + std::to_string(time(NULL)) + ""
		")"
	);

	uint64_t cardId = database.getLastInsertId();
	card.id = cardId;
	card.timeCreated = time(NULL);
	database.Close();

	if (!result)
		return InventoryCard{};

	_items.push_back(card);
	return card;
}

bool InventoryManager::SendGift(uint32_t targetId, InventoryCard cardToGift)
{

	Database database{};
	std::string query = "UPDATE player_items SET player_id = %1%, opened = 0, time = %2%  WHERE id = %3%";
	bool result = database.executeQuery(str(boost::format(query) % targetId % time(NULL) % cardToGift.id));
	database.Close();

	if (!result)
		return false;

	for (auto it = _items.begin(); it != _items.end(); it++)
	{
		if ((*it).id == cardToGift.id)
		{
			_items.erase(it);
			return true;
		}
	}
	return false;
}

bool InventoryManager::OpenGift(uint32_t cardId)
{
	bool opened = false;
	for (auto it = _items.begin(); it != _items.end(); it++)
	{
		if (it->id == cardId)
		{
			it->opened = opened = true;
			it->timeCreated = time(NULL);
		}
	}

	if (opened)
	{
		Database database{};
		database.executeQuery(str(boost::format("UPDATE player_items SET opened = 1, time = %1% WHERE id = %2%") % time(NULL) % cardId));
		database.Close();
	}

	return opened;
}

bool InventoryManager::ReceiveGift(InventoryCard cardToReceive)
{
	if (_items.size() >= MAX_INVENTORY)
		return false;

	_items.push_back(cardToReceive);
}

bool InventoryManager::HasItems()
{
	return _items.size() > 0;
}

