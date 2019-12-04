#ifndef GREEN_MED_KIT_HPP
#define GREEN_MED_KIT_HPP

#include "game_item.hpp"

#define HEALING 50

class GreenMedKit : public GameItem
{
public:
	GreenMedKit() : GameItem(GameItem::GREEN_MEDKIT, "GreenMedKit") {};

	void OnPickup(std::shared_ptr<Player> player)
	{

	}
};

#endif