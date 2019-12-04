#ifndef EQUIPMENT_MANAGER_HPP
#define EQUIPMENT_MANAGER_HPP

#include <map>
#include <array>
#include <cstdint>
#include <vector>
#include "database.hpp"

class EquipmentManager {

public:
	enum Character {
		KEN,
		HANA,
		KUMA,
		MIUMIU,
		SAI,
		URU,
		CHARACTER_COUNT,
	};

	enum EquipmentSlot {
		HEAD,
		FACE,
		BODY,
		HAND,
		BOTTOM,
		FOOT,
		BACK,
		SIDE,
		UNKNOWN,
		PRIMARY,
		SECONDARY,
		THROW,
		MELEE,
		EQUIPMENT_COUNT,
	};


	EquipmentManager();
	~EquipmentManager();

	void Load(uint32_t playerId);
	void Save(uint32_t playerId);
	void SetEquipmentPart(Character character, EquipmentSlot slot, uint64_t cardId);

	uint64_t GetEquipmentPart(Character character, EquipmentSlot slot);
	uint16_t GetCharacterCode(uint32_t characterIndex);
	uint32_t GetCharacterIndex(uint32_t characterCode);
	bool ValidateCharacter(uint16_t characterCode);
	std::array<uint64_t, 9> GetArmor(Character character);
	std::array<uint64_t, 4> GetWeapons(Character character);
	std::array<uint64_t, 13> GetAllByCharacter(Character character);
	std::array<std::array<uint32_t, 3>, 6> GetSkillCards();
	std::array<uint32_t, 3> GetSkillCardsByCharacter(Character character);
	std::array<std::array<uint64_t, 13>, 6> GetAll();

private:

	std::map<Character, uint16_t> _characters = 
	{
		{ Character::KEN, 333},
		{ Character::HANA, 343},
		{ Character::KUMA, 578},
		{ Character::MIUMIU, 579},
		{ Character::SAI, 850},
		{ Character::URU, 851},
	};
	std::array<std::array<uint64_t, 13>, 6> _equipment;
	std::array<std::array<uint32_t, 3>, 6> _skillCards;
};

#endif // !EQUIPMENT_MANAGER_HPP
