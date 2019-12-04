#ifndef _GAME_ITEM_HPP
#define _GAME_ITEM_HPP

//std
#include <memory>
#include <cstdint>
#include <string>

class Player;
class GameRoomSession;

class GameItem : public std::enable_shared_from_this<GameItem>
{

public:

	using Ptr = std::shared_ptr<GameItem>;

	enum ID : uint32_t
	{
		AMMO_CLIP = 1191182337,
		RED_MEDKIT = 1191182338,
		EVENT_ITEM = 1191182344,
		GREEN_MEDKIT = 1191182350,
		SKILL_CARD = 1191182351,
		GOLD_COIN = 1191182352,
		SILVER_COIN = 1191182353,
		BRONZE_COIN = 1191182354
	};

	GameItem(ID identifier, std::string name);
	~GameItem() = default;

	virtual void OnPickup(std::shared_ptr<Player> player) {};

private:
	ID m_item;
	std::string m_name;
};

#endif //_GAME_ITEM_HPP