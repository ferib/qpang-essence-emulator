#ifndef SQUARE_COMMAND_HPP
#define SQUARE_COMMAND_HPP

#include "command.hpp"
#include "square_session.hpp"

class SquareCommand : public Command {

public:

	SquareCommand(std::string name = "square_command", Command::Rank rank = Command::USER, std::string description = "square_command_description") : Command(name, rank, description) {};
	virtual void Execute(SquareSession* session) {};
};

#endif // !SQUARE_COMMAND_HPP
