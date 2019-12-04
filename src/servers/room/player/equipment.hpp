#ifndef EQUIPMENT_HPP
#define EQUIPMENT_HPP

#include <array>
#include <cstdint>

class Equipment
{

	typedef std::array<uint32_t, 4> weapon_container;
	typedef std::array<uint32_t, 9> armor_container;

	enum WeaponPart : uint8_t
	{
		PRIMARY = 0,
		SECONDARY = 1,
		THROW = 2,
		MELEE = 3,
	};

	enum ArmorPart : uint8_t
	{
		HEAD = 0,
		FACE = 1,
		BODY = 2,
		HAND = 3,
		BOTTOM = 4,
		FOOT = 5,
		BACK = 6,
		SIDE = 7,
		UNKNOWN = 8,
	};

public:

	Equipment();
	~Equipment();

	weapon_container GetWeapons() const;
	armor_container GetArmor() const;

	uint32_t GetDefaultWeapon();

	void SetWeapons(const weapon_container& weapons);
	void SetArmor(const armor_container& armor);

	void SetWeaponPart(const WeaponPart& part, const uint32_t& itemIdentifier);
	void SetArmorPart(const ArmorPart& part, const uint32_t& itemIdentifier);

	uint32_t GetWeaponPart(const WeaponPart& part);
	uint32_t GetArmorPart(const ArmorPart& part);

	void Clear();

private:

	weapon_container m_weapons;
	armor_container m_armor;

};

#endif