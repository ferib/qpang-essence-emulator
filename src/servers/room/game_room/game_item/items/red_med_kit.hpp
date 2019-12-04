#ifndef RED_MED_KIT_HPP
#define RED_MED_KIT_HPP

#include "game_item.hpp"

#define HEALING 50

class RedMedKit : public GameItem
{
public:
	RedMedKit() : GameItem(GameItem::RED_MEDKIT, "RedMedKit") {};

	void OnPickup(std::shared_ptr<Player> player)
	{

	}
};

#endif