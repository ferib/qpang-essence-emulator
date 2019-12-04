#ifndef RELOAD_CRANE_COMMAND_HPP
#define RELOAD_CRANE_COMMAND_HPP

#include "square_command.hpp"
#include "square_manager.hpp"
#include "reload_crane_event.hpp"

class ReloadCraneCommand : public SquareCommand
{
	
public:
	ReloadCraneCommand() : SquareCommand("ReloadCrane", Rank::GM, "This command reloads the items that are available in the crane") {};

	void Execute(SquareSession* session)
	{
		session->GetSquareManager()->LobbyServer()->SendPacket(ReloadCraneEvent{}.Compose(nullptr));
	};
};

#endif