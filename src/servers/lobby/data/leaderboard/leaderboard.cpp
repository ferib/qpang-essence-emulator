#include "leaderboard.hpp"

Leaderboard::Leaderboard()
{
	Load();
}

Leaderboard::~Leaderboard()
{
}

void Leaderboard::Load()
{
	if (_ranking.size())
	{
		sLogger->Get()->info("Leaderboard: pushing current ranking to old ranking");
		_oldRanking = _ranking;
	}


	Database database{};
	auto result = database.storeQuery("SELECT id, experience FROM players ORDER BY experience DESC");
	if (result)
	{
		sLogger->Get()->info("Loading new leaderboard");

		int32_t rank = 1;
		do
		{
			uint32_t playerId = result->getNumber<uint32_t>("id");
			Position pos{};
			pos.rank = rank;

			auto oldPos = _oldRanking.find(playerId);
			if (oldPos != _oldRanking.end())
			{
				pos.didIncrease = (rank - oldPos->second.rank) < 0;
				pos.difference = oldPos->second.rank - rank;
			}
			_ranking[playerId] = pos;
			result->next();
			rank++;
		} while (result->hasNext());
	}
	database.Close();
}

Leaderboard::Position Leaderboard::GetRank(uint32_t playerId)
{
	auto set = _ranking.find(playerId);
	if (set != _ranking.end())
		return set->second;
	else
		return Position{};
}
