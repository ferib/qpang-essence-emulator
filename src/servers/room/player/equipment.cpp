#include "equipment.hpp"

Equipment::Equipment() : m_weapons({}), m_armor({})
{
}

Equipment::~Equipment()
{
}

Equipment::weapon_container Equipment::GetWeapons() const
{
	return m_weapons;
}

Equipment::armor_container Equipment::GetArmor() const
{
	return m_armor;
}

uint32_t Equipment::GetDefaultWeapon()
{
	for (const uint32_t& itemIdentifier : m_weapons)
	{
		if (itemIdentifier != NULL)
		{
			return itemIdentifier;
		}
	}

	return uint32_t(0);
}

void Equipment::SetWeapons(const weapon_container& weapons)
{
	m_weapons = weapons;
}

void Equipment::SetArmor(const armor_container& armor)
{
	m_armor = armor;
}

void Equipment::SetWeaponPart(const WeaponPart& part, const uint32_t& itemIdentifier)
{
	m_weapons[part] = itemIdentifier;
}

void Equipment::SetArmorPart(const ArmorPart& part, const uint32_t& itemIdentifier)
{
	m_armor[part] = itemIdentifier;
}

uint32_t Equipment::GetWeaponPart(const WeaponPart& part)
{
	return m_weapons[part];
}

uint32_t Equipment::GetArmorPart(const ArmorPart& part)
{
	return m_armor[part];
}

void Equipment::Clear()
{
	m_weapons = {};
	m_armor = {};
}
