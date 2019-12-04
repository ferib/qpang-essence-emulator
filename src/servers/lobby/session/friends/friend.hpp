#ifndef FRIEND_HPP
#define FRIEND_HPP

#include <cstdint>
#include <string>

struct Friend {

	Friend() {};
	Friend(uint32_t id, uint32_t fromId, uint32_t toPlayerId, std::string nickname, uint8_t level, uint8_t state)
	{
		this->id = id;
		this->fromId = fromId;
		this->toPlayerId = toPlayerId;
		this->nickname = nickname;
		this->level = level;
		this->state = state;
	}

	uint32_t id;
	uint32_t fromId;
	uint32_t toPlayerId;
	std::string nickname;
	uint8_t level;
	uint8_t state;
};

#endif // !FRIEND_HPP
