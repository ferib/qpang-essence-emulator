#ifndef USERS_ONLLINE_HPP
#define USERS_ONLLINE_HPP

#include "square_command.hpp"
#include "square_manager.hpp"
#include "square.hpp"

#include <vector>
#include <cstdint>

class UsersOnlineCommand : public SquareCommand
{
	
public:
	UsersOnlineCommand() : SquareCommand("OnlineCommand", Rank::USER, "This command shows you the amount of players online") {};

	void Execute(SquareSession* session)
	{

		uint32_t usersOnline = 0;
		auto list = session->GetSquareManager()->List();

		for(auto square : list)
			usersOnline += square->List().size();

		session->Whisper(std::to_string(usersOnline));
	};
};

#endif