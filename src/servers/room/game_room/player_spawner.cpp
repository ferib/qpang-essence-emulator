#include "player_spawner.hpp"

#include "database.hpp"

PlayerSpawner::PlayerSpawner()
{
}

PlayerSpawner::~PlayerSpawner()
{
}


void PlayerSpawner::Load(uint8_t modeIdentifier, uint8_t mapIdentifier)
{
	srand(time(NULL));

	std::lock_guard<std::mutex> lg(m_spawnMx);

	Database database{};

	auto result = database.storeQuery(str(boost::format(
		"SELECT * FROM map_spawns INNER JOIN positions ON positions.id = map_spawns.position_id INNER JOIN maps ON maps.id = map_spawns.map_id INNER JOIN game_modes ON game_modes.id = map_spawns.game_mode_id WHERE maps.map_id = %1% AND game_modes.mode_id = %2%")
		% std::to_string(mapIdentifier) % std::to_string(modeIdentifier)).c_str());

	if (result != nullptr)
	{
		do
		{
			float x = result->getNumber<float>("x");
			float y = result->getNumber<float>("y");
			float z = result->getNumber<float>("z");
			uint8_t teamId = result->getNumber<uint32_t>("team");

			auto team = m_spawns.find(teamId);
			Spawn spawn{ x, y, z };

			if (team != m_spawns.end())
				team->second.push_back(spawn);
			else
				m_spawns[teamId] = std::vector<Spawn>{spawn};

			result->next();
		} while (result->hasNext());
	}

	database.Close();
}

void PlayerSpawner::AddSpawn(uint8_t team, Spawn spawn)
{
	std::lock_guard<std::mutex> lg(m_spawnMx);

	m_spawns[team].push_back(spawn);
}

Spawn PlayerSpawner::GetRandomSpawnForTeam(uint8_t team)
{
	std::lock_guard<std::mutex> lg(m_spawnMx);

	auto it = m_spawns.find(team);

	if (it != m_spawns.end())
	{
		if (it->second.size() > 0)
		{
			uint32_t index = rand() % it->second.size();
			return it->second.at(index);
		}
	}

	return Spawn{ NULL, NULL, NULL };
}
