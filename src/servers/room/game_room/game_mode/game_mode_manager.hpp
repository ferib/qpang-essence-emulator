#ifndef _GAME_MODE_MANAGER_HPP
#define _GAME_MODE_MANAGER_HPP

#include "game_mode.hpp"
#include "logger.hpp"

#include <map>
#include <cstdint>

class GameModeManager
{

	typedef std::map<uint8_t, GameMode*> m_mappedModes;

public:

	GameModeManager();
	~GameModeManager();
	void Load();

	GameMode* GetMode(const uint8_t &gameModeId);
private:
	m_mappedModes m_gameModes = m_mappedModes{};
};

#endif //_GAME_MODE_MANAGER_HPP