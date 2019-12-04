#ifndef _FREE_FOR_ALL_HPP
#define _FREE_FOR_ALL_HPP

//std
#include <string>
#include <memory>
#include "game_mode.hpp"
#include "mode.hpp"
#include "player_session.hpp"

class GameRoom;

class FreeForAll : public GameMode
{
	typedef GameMode Parent;
public:
	FreeForAll() = default;
	~FreeForAll() = default;

	void OnApply(const std::shared_ptr<GameRoom>& room) override;
	bool IsTeamMode() override;

	std::string GetName() override;
	uint8_t GetModeIdentifier() override;
};

#endif //_TEAM_DEATH_MATCH_HPP