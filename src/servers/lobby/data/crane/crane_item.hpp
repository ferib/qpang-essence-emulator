#ifndef CRANE_ITEM_HPP
#define CRANE_ITEM_HPP

#include <cstdint>

struct CraneItem {

	CraneItem(uint32_t id, uint32_t itemId, uint32_t period, uint8_t periodType, uint8_t itemType)
	{
		this->id = id;
		this->itemId = itemId;
		this->period = period;
		this->periodType = periodType;
		this->itemType = itemType;
	}

	uint32_t id;
	uint32_t itemId;
	uint16_t period;
	uint8_t periodType;
	uint8_t itemType;
};

#endif