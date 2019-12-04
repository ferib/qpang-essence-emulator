#include "square_command_handler.hpp"
#include "execute_command_exception.hpp"
#include "online_command.hpp"


//TODO: Refactor this (had issues with them pointers..)
SquareCommandHandler::SquareCommandHandler()
{

	sLogger->Get()->info("Loading Square Commands");

	Set("test", new TestCommand());
	Set("reloadcrane", new ReloadCraneCommand());
	Set("reloadleaderboard", new ReloadLeaderboardCommand());
	Set("online", new UsersOnlineCommand());

	sLogger->Get()->info("{0:d} commands were loaded!", _commands.size());
}

SquareCommandHandler::~SquareCommandHandler()
{
}

bool SquareCommandHandler::TryExecute(SquareSession* session, std::string commandName)
{
	
	auto set = _commands.find(commandName);
	if (set == _commands.cend())
		return false;

	auto* command = set->second;
	if (command->GetRank() <= session->Info()->Rank() || (command->GetRank() == Command::GM && session->Info()->Rank() == 3))
	{
		try
		{
			sLogger->Get()->info("{0} is trying toe execute command {1}", session->Info()->Nickname(), command->Name());
			command->Execute(session);
		}
		catch (const std::exception&)
		{
			throw ExecuteCommandException("Failed to execute packet");
		}

		return true;
	}
	return false;
}

