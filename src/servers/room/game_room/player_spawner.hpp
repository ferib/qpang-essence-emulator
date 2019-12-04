#ifndef _PLAYER_SPAWNER_HPP
#define _PLAYER_SPAWNER_HPP

#include <unordered_map>
#include <vector>
#include <string>
#include <mutex>
#include <cstdint>

#include "spawn.hpp"

class PlayerSpawner
{

public:
	PlayerSpawner();
	~PlayerSpawner();

	void Load(uint8_t modeIdentifier, uint8_t mapIdentifier);

	void AddSpawn(uint8_t team, Spawn spawn);

	Spawn GetRandomSpawnForTeam(uint8_t team);

private:
	std::unordered_map<uint8_t, std::vector<Spawn>> m_spawns = {};
	std::mutex m_spawnMx;
};

#endif // !_PLAYER_SPAWNER_HPP
