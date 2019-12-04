#ifndef LEADERBOARD_HPP
#define LEADERBOARD_HPP

#include <cstdint>
#include <map>
#include "database.hpp"
#include "logger.hpp"

class Leaderboard
{

public:
	struct Position {
		uint32_t rank;
		uint8_t didIncrease;
		uint32_t difference;
	};


	Leaderboard();
	~Leaderboard();

	Position GetRank(uint32_t playerId);
	void Load();
private:
	Logger* _logger;
	std::map<uint32_t, Position> _ranking;
	std::map<uint32_t, Position> _oldRanking;
};

#endif //_LOBBY_SERVER_H