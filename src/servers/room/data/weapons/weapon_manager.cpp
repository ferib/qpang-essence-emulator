#include "weapon_manager.hpp"

WeaponManager::WeaponManager()
{
	Load();
}

WeaponManager::~WeaponManager()
{
}

void WeaponManager::Load()
{
	_weapons.clear();

	Database database{};

	auto result = database.storeQuery("SELECT * FROM weapons");
	if (result != nullptr)
	{
		do
		{
			uint32_t itemId = result->getNumber<uint32_t>("item_id");
			uint16_t damage = result->getNumber<uint32_t>("damage");
			std::string codeName = result->getString("code_name");
			uint8_t effectChance = result->getNumber<uint32_t>("chance");
			uint8_t effectId = result->getNumber<uint32_t>("effect_id");
			uint32_t effectDuration = result->getNumber<uint32_t>("duration");

			_weapons[itemId] = Weapon{ itemId, damage, codeName, effectId, effectChance, effectDuration };

			result->next();
		} while (result->hasNext());
	}

	database.Close();
}

Weapon WeaponManager::GetWeapon(uint32_t itemId)
{
	return _weapons[itemId];
}

uint16_t WeaponManager::GetDamage(uint32_t itemId)
{
	return GetWeapon(itemId).damage;
}

std::string WeaponManager::GetName(uint32_t itemId)
{
	return GetWeapon(itemId).name;
}

uint8_t WeaponManager::GetEffect(uint32_t itemId)
{
	auto weapon = GetWeapon(itemId);
	return (rand() % 100) < GetWeapon(itemId).effectChance ? weapon.effectId : NULL;
}
