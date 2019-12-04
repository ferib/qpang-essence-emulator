#ifndef _TEAM_DEATH_MATCH_HPP
#define _TEAM_DEATH_MATCH_HPP

//std
#include <string>
#include <memory>
#include "game_mode.hpp"
#include "mode.hpp"
#include "free_for_all.hpp"

class GameRoom;

class TeamDeathMatch : public FreeForAll
{
	typedef FreeForAll Parent;
public:
	TeamDeathMatch() = default;
	~TeamDeathMatch() = default;

	void OnApply(const std::shared_ptr<GameRoom>& room) override;
	void OnPlayerKill(const std::shared_ptr<GameRoomSession>& roomSession, const Player::Ptr& killer, const Player::Ptr& target) override;
	bool IsTeamMode() override;

	std::string GetName() override;
	uint8_t GetModeIdentifier() override;
};

#endif //_TEAM_DEATH_MATCH_HPP