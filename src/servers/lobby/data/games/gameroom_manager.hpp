#ifndef	GAMEROOM_MANAGER_HPP
#define GAMEROOM_MANAGER_HPP

#include <string>
#include <cstdint>
#include <vector>
#include "gameroom.hpp"

class GameRoomManager {
	
public:
	void UpdateRoom(uint32_t id, std::string name, uint8_t map, uint8_t mode, uint8_t currPlayers, uint8_t maxPlayers, uint8_t meleeOnly, uint8_t state);
	void RemoveRoom(uint32_t roomId);
	inline std::vector<GameRoom> List() { return _rooms; };

private:
	std::vector<GameRoom> _rooms;
};

#endif