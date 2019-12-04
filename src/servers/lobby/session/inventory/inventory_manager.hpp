#ifndef INVENTORY_MANAGER_HPP
#define INVENTORY_MANAGER_HPP

#define MAX_INVENTORY 199

#include <cstdint>
#include <vector>
#include "database.hpp"
#include "inventory_card.hpp"
#include <time.h>

class InventoryManager {

public:
	InventoryManager();
	~InventoryManager();

	void Load(uint32_t playerId);
	std::vector<InventoryCard> List();

	InventoryCard GetItemByCardId(uint32_t cardId);
	bool RemoveItem(uint32_t cardId);
	InventoryCard AddItem(InventoryCard card);
	bool SendGift(uint32_t targetId, InventoryCard cardToGift);
	bool OpenGift(uint32_t cardId);
	bool ReceiveGift(InventoryCard cardToReceive);
	bool HasItems();
private:
	std::vector<InventoryCard> _items;
	bool _hasItems;
};

#endif // !INVENTORY_MANAGER_HPP
