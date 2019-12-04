#ifndef _SKILL_HPP
#define _SKILL_HPP

#include <cstdint>
#include <string>

struct Skill
{
	//default ctor for map
	Skill() {};

	Skill(std::string name, uint32_t itemId, uint32_t pointCost, uint32_t duration)
	{
		this->name = name;
		this->itemId = itemId;
		this->pointCost = pointCost;
		this->duration = duration;
	}

	std::string name;
	uint32_t itemId;
	uint32_t pointCost;
	uint32_t duration;
};

#endif _SKILL_HPP