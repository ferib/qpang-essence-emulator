#ifndef _GAME_ITEM_MANAGER_HPP
#define _GAME_ITEM_MANAGER_HPP

#include <mutex>
#include <map>
#include <memory>
#include <vector>

#include "tickable.hpp"
#include "spawn.hpp"
#include "player.hpp"

#include "ammo_clip.hpp"
#include "green_med_kit.hpp"
#include "red_med_kit.hpp"
#include "skill_book.hpp"

class GameItemManager
{

	typedef std::lock_guard<std::mutex> Lock;

	struct GameItemSpawn 
	{
		uint32_t m_identifier;
		Spawn spawn;
	};

public:
	GameItemManager() = default;
	~GameItemManager() = default;

	void Load(uint8_t map);

	void RemovePossibleItem(uint32_t itemId);

	void UseItem(Player::Ptr player, uint32_t gameItemSpawnIdentifier);
	void AddItem(uint32_t gameItemSpawnIdentifier);
	
	void Sync(std::shared_ptr<GameRoomSession> roomSession);
	void SyncFor(Player::Ptr player);

private:

	std::mutex m_itemMx;
	std::mutex m_positionGameItemMx;

	std::map<uint32_t, GameItem::Ptr> m_possibleItems = {
		{ GameItem::AMMO_CLIP, std::make_shared<AmmoClip>() },
		{ GameItem::GREEN_MEDKIT, std::make_shared<GreenMedKit>() },
		{ GameItem::RED_MEDKIT, std::make_shared<RedMedKit>() },
		{ GameItem::SKILL_CARD, std::make_shared<SkillBook>() },
	};

	std::vector<uint32_t> m_itemIds = {
		GameItem::AMMO_CLIP,
		GameItem::GREEN_MEDKIT,
		GameItem::RED_MEDKIT,
		GameItem::SKILL_CARD,	
	};

	/* gameitemspawn m_identifier --> GameItem ID */
	std::map<uint32_t, uint32_t> m_positionedGameItems;

	std::vector<GameItemSpawn> m_spawnPositions;
};
#endif //_GAME_ITEM_MANAGER_HPP