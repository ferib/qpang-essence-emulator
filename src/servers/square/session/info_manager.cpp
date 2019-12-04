#include "info_manager.hpp"

void InfoManager::SetEquipment(std::array<uint32_t, 9> equipment)
{
	_equipment = equipment;
}

std::array<uint32_t, 9> InfoManager::Equipment()
{
	return _equipment;
}

void InfoManager::SetId(uint32_t playerId)
{
	_playerId = playerId;
}

void InfoManager::SetLevel(uint32_t level)
{
	_level = level;
}
void InfoManager::SetCharacter(uint16_t character)
{
	_character = character;
}
void InfoManager::SetPrestige(uint32_t prestige)
{
	_prestige = prestige;
}
void InfoManager::SetNickname(std::string nickname)
{
	_nickname = nickname;
}
void InfoManager::SetRank(uint8_t rank)
{
	_rank = rank;
}

uint32_t InfoManager::Id()
{
	return _playerId;
}
uint32_t InfoManager::Prestige()
{
	return _prestige;
}
uint32_t InfoManager::Level()
{
	return _level;
}
uint16_t InfoManager::Character()
{
	return _character;
}

uint8_t InfoManager::Rank()
{
	return _rank;
}

std::string InfoManager::Nickname()
{
	return _nickname;
}

void InfoManager::SetPosition(std::array<float, 3> position)
{
	_position = position;
}

std::array<float, 3> InfoManager::Position()
{
	return _position;
}

void InfoManager::SetState(uint32_t state)
{
	_state = state;
}

uint32_t InfoManager::State()
{
	return _state;
}


