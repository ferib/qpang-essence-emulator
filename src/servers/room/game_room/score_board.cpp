#include "score_board.hpp"

void ScoreBoard::AddPlayer(ScoreBoard::Player player)
{
	m_players.push_back(player);
}

std::vector<ScoreBoard::Player> ScoreBoard::GetResults()
{
	return m_players;
}
