#ifndef WEAPON_MANAGER_HPP
#define WEAPON_MANAGER_HPP

#include "database.hpp"
#include "weapon.hpp"

#include <map>
#include <cstdint>
#include <string>
#include "tnlBitSet.h"

class WeaponManager
{
public:
	WeaponManager();
	~WeaponManager();

	void Load();

	Weapon GetWeapon(uint32_t itemId);
	uint16_t GetDamage(uint32_t itemId);
	std::string GetName(uint32_t itemId);
	uint8_t GetEffect(uint32_t itemId);

private:
	std::map<uint32_t, Weapon> _weapons;
};


#endif // !WEAPON_MANAGER_HPP