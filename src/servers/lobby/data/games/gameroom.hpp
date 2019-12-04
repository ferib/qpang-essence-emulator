#ifndef GAMEROOM_STRUCT_HPP
#define GAMEROOM_STRUCT_HPP

#include <cstdint>
#include <string>

struct GameRoom {
	
	GameRoom(uint32_t id, std::string name, uint8_t map, uint8_t mode, uint8_t currPlayers, uint8_t maxPlayers, uint8_t meleeOnly, uint8_t state)
	{
		this->id = id;
		this->name = name;
		this->map = map;
		this->mode = mode;
		this->currPlayers = currPlayers;
		this->maxPlayers = maxPlayers;
		this->meleeOnly = meleeOnly;
		this->state = state;
	}
	
	uint32_t id;
	std::string name;
	uint8_t map;
	uint8_t mode;
	uint8_t currPlayers;
	uint8_t maxPlayers;
	uint8_t meleeOnly;
	uint8_t state;
};
#endif // !GAMEROOM_STRUCT_HPP