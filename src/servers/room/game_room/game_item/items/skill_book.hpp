#ifndef SKILL_BOOK_HPP
#define SKILL_BOOK_HPP

#include "game_item.hpp"

class SkillBook : public GameItem
{
public:
	SkillBook() : GameItem(GameItem::SKILL_CARD, "SkillBook") {};

	void OnPickup(std::shared_ptr<Player> player)
	{

	}
};

#endif