#ifndef _WEAPON_HPP
#define _WEAPON_HPP

#include <cstdint>
#include <string>

struct Weapon
{
	//default ctor for map
	Weapon() {};

	Weapon(uint32_t itemId, uint16_t damage, std::string name, uint8_t effectId, uint8_t effectChance, uint32_t effectDuration)
	{
		this->itemId = itemId;
		this->damage = damage;
		this->name = name;
		this->effectId = effectId;
		this->effectChance = effectChance;
		this->effectDuration = effectDuration;
	}

	uint32_t itemId;
	uint16_t damage;
	std::string name;
	uint8_t effectId, effectChance;
	uint32_t effectDuration;
};

#endif _WEAPON_HPP