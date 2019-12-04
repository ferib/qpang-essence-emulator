#include "game_mode_manager.hpp"
#include "team_death_match.hpp"
#include "mode.hpp"
#include "practice.hpp"
#include "free_for_all.hpp"

GameModeManager::GameModeManager()
{
	Load();
}

GameModeManager::~GameModeManager()
{

}

void GameModeManager::Load()
{
	sLogger->Get()->debug("GameModeManager Load");

	m_gameModes = {
		{DEATH_MATCH, new FreeForAll()},
		{TEAM_DEATH_MATCH, new TeamDeathMatch()},
		{PRACTICE, new Practice()},
	};
}

GameMode* GameModeManager::GetMode(const uint8_t& gameModeId)
{
	sLogger->Get()->debug("GameModeManager GetMode");


	for (auto set : m_gameModes)
	{
		if (set.first == gameModeId)
			return set.second;
	}

	if (!m_gameModes.empty())
		return m_gameModes.begin()->second;

	throw "There are no game modes available";
}
