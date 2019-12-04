#ifndef ANNOUNCE_COMMAND_HPP
#define ANNOUNCE_COMMAND_HPP

#include "square_command.hpp"
#include "square_manager.hpp"

#include "announcement_event.hpp"

class AnnouncementCommand : public SquareCommand
{
	
public:
	AnnouncementCommand() : SquareCommand("AnnouncementCommand", Rank::GM, "Announce something across the whole server") {};

	void Execute(SquareSession* session)
	{
		//TODO: Add argumented commands

	};
};

#endif