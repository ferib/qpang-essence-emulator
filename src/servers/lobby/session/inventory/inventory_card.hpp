#ifndef INVENTORY_CARD_HPP
#define INVENTORY_CARD_HPP

#include <cstdint>

struct InventoryCard {

	InventoryCard()
	{
		this->id = NULL;
		this->itemId = NULL;
		this->period = NULL;
		this->periodType = NULL;
		this->itemType = NULL;
		this->opened = NULL;
		this->giftable = NULL;
		this->boostLevel = NULL;
		this->boosted = NULL;
		this->timeCreated = NULL;
		this->ownerId = NULL;
	}
	InventoryCard(uint32_t ownerId, uint32_t id, uint32_t itemId, uint16_t period, uint8_t periodType, uint8_t itemType,
		uint8_t opened, uint8_t giftable, uint8_t boostLevel, uint8_t boosted, uint32_t timeCreated)
	{
		this->ownerId = ownerId;
		this->id = id;
		this->itemId = itemId;
		this->period = period;
		this->periodType = periodType;
		this->itemType = itemType;
		this->opened = opened;
		this->giftable = giftable;
		this->boostLevel = boostLevel;
		this->boosted = boosted;
		this->timeCreated = timeCreated;
	};

	uint32_t ownerId;
	uint32_t id;
	uint32_t itemId;
	uint16_t period;
	uint8_t periodType;
	uint8_t itemType;
	uint8_t opened;
	uint8_t giftable;
	uint8_t boostLevel;
	uint8_t boosted;
	uint32_t timeCreated;
};

#endif // !INVENTORY_CARD_HPP
