#ifndef SHOP_ITEM_HPP
#define SHOP_ITEM_HPP

#include <cstdint>
#include <string>

struct ShopItem {

	ShopItem(std::string name, uint32_t seqId, uint32_t itemId, uint8_t itemType, uint8_t payType, uint32_t price, uint8_t useType, uint16_t period, uint8_t minLevel
	, uint8_t state, uint16_t soldCount, uint16_t stock) 
	{
		this->name = name;
		this->sequenceId = seqId;
		this->itemId = itemId;
		this->itemType = itemType;
		this->payType = payType;
		this->price = price;
		this->useType = useType;
		this->period = period;
		this->minLevel = minLevel;
		this->state = state;
		this->soldCount = soldCount;
		this->stock = stock;
	};


	std::string name;
	uint32_t sequenceId;
	uint32_t itemId;
	uint8_t itemType;
	uint8_t payType;
	uint32_t price;
	uint8_t useType;
	uint16_t period;
	uint8_t minLevel;
	uint8_t state;
	uint16_t soldCount;
	uint16_t stock;
};

#endif // !SHOP_ITEM_HPP
