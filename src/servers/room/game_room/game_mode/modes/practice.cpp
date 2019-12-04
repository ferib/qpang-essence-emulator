#include "practice.hpp"
#include "game_room.hpp"
#include "mode.hpp"

void Practice::OnApply(const std::shared_ptr<GameRoom>& room)
{
	room->BalancePlayers();
}

bool Practice::IsTeamMode()
{
	return false;
}

std::string Practice::GetName()
{
	return "Practice";
}

uint8_t Practice::GetModeIdentifier()
{
	return Mode::PRACTICE;
}
