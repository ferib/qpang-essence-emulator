#include "team_death_match.hpp"
#include "game_room.hpp"

void TeamDeathMatch::OnApply(const std::shared_ptr<GameRoom>& room)
{
	room->BalancePlayers();
}

void TeamDeathMatch::OnPlayerKill(const std::shared_ptr<GameRoomSession>& roomSession, const Player::Ptr & killer, const Player::Ptr & target)
{
	Parent::OnPlayerKill(roomSession, killer, target);
}

bool TeamDeathMatch::IsTeamMode()
{
	return true;
}

std::string TeamDeathMatch::GetName()
{
	return "Team Death Match";
}

uint8_t TeamDeathMatch::GetModeIdentifier()
{
	return Mode::TEAM_DEATH_MATCH;
}
