#ifndef _LEVEL_HPP
#define _LEVEL_HPP

#include <cstdint>
#include <string>

struct Level
{
	//default ctor for map
	Level() {};

	Level(uint32_t level, std::string name, uint32_t exp, uint32_t don, uint32_t cash, uint32_t coin, uint32_t experience)
	{
		this->level = level;
		this->name = name;
		this->don = don;
		this->cash = cash;
		this->coin = coin;
		this->experience = experience;
	}

	uint32_t level;
	std::string name;
	uint32_t don, cash, coin, experience;
};

#endif _WEAPON_HPP