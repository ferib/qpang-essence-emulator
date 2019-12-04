#ifndef AMMO_CLIP_HPP
#define AMMO_CLIP_HPP

#include "game_item.hpp"

class AmmoClip : public GameItem
{
public:
	AmmoClip() : GameItem(GameItem::AMMO_CLIP, "AmmoClip") {};

	void OnPickup(std::shared_ptr<Player> player)
	{

	}
};

#endif