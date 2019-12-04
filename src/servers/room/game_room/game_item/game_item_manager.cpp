#include "game_item_manager.hpp"

#include "game.hpp"

#include "gc_game_item.hpp"

void GameItemManager::Load(uint8_t map)
{
	m_spawnPositions.clear();

	Database database{};

	auto result = database.storeQuery(str(boost::format(
		"SELECT game_item_spawns.id, positions.x, positions.y, positions.z FROM game_item_spawns INNER JOIN positions ON positions.id = game_item_spawns.position_id INNER JOIN maps ON maps.id = game_item_spawns.map_id WHERE maps.map_id = %1%")
		% std::to_string(map)).c_str());

	if (result != nullptr)
	{
		do
		{
			uint32_t identifier = result->getNumber<uint32_t>("id");
			float x = result->getNumber<float>("x");
			float y = result->getNumber<float>("y");
			float z = result->getNumber<float>("z");

			GameItemSpawn spawn{ identifier, {x, y, z} };

			m_positionedGameItems[identifier] = 0;
			AddItem(identifier);
			AddItem(identifier);
			m_spawnPositions.push_back(spawn);

			result->next();
		} while (result->hasNext());
	}

	database.Close();
}

void GameItemManager::UseItem(Player::Ptr player, uint32_t gameItemSpawnIdentifier)
{
	Lock l(m_positionGameItemMx);
	Lock l2(m_itemMx);

	const uint32_t gameItem = m_positionedGameItems[gameItemSpawnIdentifier];

	m_possibleItems[gameItem]->OnPickup(player);
}

void GameItemManager::AddItem(uint32_t gameItemSpawnIdentifier)
{
	srand(time(NULL));

	Lock l(m_positionGameItemMx);
	Lock l2(m_itemMx);

	const uint32_t itemId = m_itemIds[rand() % m_itemIds.size()];

	m_positionedGameItems[gameItemSpawnIdentifier] = itemId;
}

void GameItemManager::Sync(std::shared_ptr<GameRoomSession> roomSession)
{
	Lock l(m_positionGameItemMx);

}
