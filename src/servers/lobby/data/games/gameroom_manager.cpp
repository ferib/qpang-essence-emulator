#include "gameroom_manager.hpp"

void GameRoomManager::UpdateRoom(uint32_t id, std::string name, uint8_t map, uint8_t mode, uint8_t currPlayers, uint8_t maxPlayers, uint8_t meleeOnly, uint8_t state)
{
	for (auto& room : _rooms)
	{
		if (room.id == id)
		{
			if (currPlayers <= 0)
				return RemoveRoom(id);

			room = GameRoom{ id, name, map, mode, currPlayers, maxPlayers, meleeOnly, state };
			return;
		}
	}

	_rooms.push_back(GameRoom{ id, name, map, mode, currPlayers, maxPlayers, meleeOnly, state });
};

void GameRoomManager::RemoveRoom(uint32_t roomId)
{
	for (auto it = _rooms.begin(); it != _rooms.end(); it++)
	{
		if ((*it).id == roomId)
		{
			_rooms.erase(it);
			return;
		}
	}
};


