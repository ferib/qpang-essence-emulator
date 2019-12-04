#ifndef OFFLINE_PLAYER_HPP
#define OFFLINE_PLAYER_HPP

#include <cstdint>
#include <string>
#include <array>

struct OfflinePlayer {

	enum Type {
		MINIMAL,
		MEDIUM,
		MAXIMAL
	};

	OfflinePlayer() { playerId = NULL; };
	OfflinePlayer(uint32_t playerId, std::string nickname, uint8_t level, uint8_t rank, uint32_t experience, uint32_t prestige, uint16_t defaultCharacter, std::array<uint32_t, 13> equipment)
	{
		this->playerId = playerId;
		this->nickname = nickname;
		this->level = level;
		this->rank = rank;
		this->experience = experience;
		this->prestige = prestige;
		this->character = defaultCharacter;
		this->equipment = equipment;
	}
	
	uint32_t playerId;
	std::string nickname;
	uint8_t level;
	uint8_t rank;
	uint32_t experience;
	uint32_t prestige;
	uint16_t character;
	std::array<uint32_t, 13> equipment;
};

#endif