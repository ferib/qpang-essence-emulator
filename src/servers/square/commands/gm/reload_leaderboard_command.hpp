#ifndef RELOAD_LEADERBOARD_HPP
#define RELOAD_LEADERBOARD_HPP

#include "square_command.hpp"
#include "square_manager.hpp"
#include "reload_leaderboard_event.hpp"

class ReloadLeaderboardCommand : public SquareCommand
{
	
public:
	ReloadLeaderboardCommand() : SquareCommand("ReloadLeaderboard", Rank::GM, "This command refreshes the leaderboard") {};

	void Execute(SquareSession* session)
	{
		session->GetSquareManager()->LobbyServer()->SendPacket(ReloadLeaderboardEvent{}.Compose(nullptr));
	};
};

#endif