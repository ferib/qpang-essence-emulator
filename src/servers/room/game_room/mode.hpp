#ifndef MODE_HPP
#define MODE_HPP

#include <cstdint>

enum Mode : uint8_t
{
	DEATH_MATCH = 1,
	TEAM_DEATH_MATCH = 2,
	ESSENCE = 3,
	VIP = 4,
	PRACTICE = 5,
	PUBLIC_ENEMY = 6,
	PVE = 7,
};

#endif