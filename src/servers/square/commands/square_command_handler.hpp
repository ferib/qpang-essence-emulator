#ifndef SQUARE_COMMAND_HANDLER_HPP
#define SQUARE_COMMAND_HANDLER_HPP

#include <string>
#include <map>
#include <boost/format.hpp>
#include "command_handler.hpp"
#include "square_command.hpp"
#include "square_session.hpp"
#include "test_command.hpp"
#include "reload_crane_command.hpp"
#include "reload_leaderboard_command.hpp"

class SquareCommandHandler : public CommandHandler<SquareCommand>
{
public:
	SquareCommandHandler();
	~SquareCommandHandler();

	bool TryExecute(SquareSession* session, std::string commandName);
private:
	Logger* _logger;
};

#endif // !SQUARE_COMMAND_HANDLER_HPP
