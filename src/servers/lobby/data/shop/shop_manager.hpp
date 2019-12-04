#ifndef SHOP_MANAGER_HPP
#define SHOP_MANAGER_HPP

#include "shop_item.hpp"
#include "database.hpp"
#include "logger.hpp"
#include <vector>
#include "inventory_card.hpp"

class ShopManager {
public:
	ShopManager();
	~ShopManager();

	ShopItem GetItemBySequenceId(uint32_t seqId);
	ShopItem GetItemByItemId(uint32_t itemId);
	InventoryCard Buy(ShopItem item, uint32_t playerId);
	void Load();
	std::vector<ShopItem> List();
private:
	std::vector<ShopItem> _items;
};

#endif // !SHOP_MANAGER_HPP
