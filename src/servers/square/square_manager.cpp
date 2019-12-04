#include "square_manager.hpp"
#include "square_command_handler.hpp"
#include <boost/lexical_cast.hpp>
#include "update_list_event.hpp"

SquareManager::SquareManager()
{
	_commandHandler = new SquareCommandHandler();
}


SquareManager::~SquareManager()
{

}

std::shared_ptr<SquareSession> SquareManager::FindSession(uint32_t playerId)
{
	for (auto session : _sessions)
	{
		if (session->GetPlayerId() == playerId)
			return session;
	}

	return nullptr;
}

void SquareManager::AddSession(std::shared_ptr<SquareSession> session)
{
	_sessions.push_back(session);
}

std::vector<std::shared_ptr<Square>> SquareManager::List()
{

	if (!_squares.size())
	{
		AddSquare();
	}

	return _squares;
}

std::shared_ptr<Square> SquareManager::GetSquare(uint32_t squareId)
{
	for (auto square : _squares)
		if (square->Id() == squareId)
			return square;

	return nullptr;
}

std::shared_ptr<Square> SquareManager::GetAvailableSquare()
{
	for (auto square : _squares)
	{
		if (square->List().size() < square->MaxCapacity() - (square->MaxCapacity() / 5))
			return square;
	}

	if (_squares.size() >= 15)
		return *_squares.begin();

	return AddSquare();
}

void SquareManager::Broadcast(ServerPacket packet)
{
	for (auto square : _squares)
		square->SendPacket(packet);
}

void SquareManager::SetLobbyServer(std::shared_ptr<Connection> lobbyServer)
{
	_lobbyServer = lobbyServer;
}

void SquareManager::RemoveSession(uint32_t playerId)
{
	for (auto it = _sessions.begin(); it != _sessions.end(); it++)
	{
		if ((*it)->Info()->Id() == playerId)
		{
			auto square = (*it)->GetSquare();
			if (square)
			{
				(*it)->GetSquare()->RemovePlayer((*it)->Info()->Id());
				if (square->Size() <= 0)
				{
					for (auto sqIt = _squares.begin(); sqIt != _squares.end(); sqIt++)
					{
						if ((*sqIt)->Id() == square->Id())
						{
							_squares.erase(sqIt);
							break;
						}
					}
				}

			}
			_sessions.erase(it);
			break;
		}
	}
}

std::shared_ptr<Connection> SquareManager::LobbyServer()
{
	return _lobbyServer;
}

std::shared_ptr<Square> SquareManager::AddSquare()
{
	uint32_t squareId = 1;
	std::string squareName = sSettings->GetSetting("square_name");
	uint32_t squareCapacity = boost::lexical_cast<uint32_t>(sSettings->GetSetting("square_capacity"));

	for (auto square : _squares)
	{
		if (square->Id() <= squareId)
		{
			squareId = square->Id() + 1;
		}
	}

	sLogger->Get()->info("Adding new square: {0:d}", squareId);
	auto square = std::make_shared<Square>(squareId, squareName, squareCapacity);
	_squares.push_back(square);

	return square->weak_from_this().lock();
}


bool SquareManager::HandleMessage(SquareSession* session, std::string message)
{
	std::string commandPrefix = sSettings->GetSetting("command_prefix");

	//If message is same size as prefix alone, obviously no command is called..
	if (commandPrefix.size() == message.size())
		return true;

	std::size_t possiblePrefixPosition = message.find(commandPrefix);

	//If the commandPrefix is not found in message
	if (possiblePrefixPosition == std::string::npos)
		return true;

	//Check if commandPrefix is at the start
	if (possiblePrefixPosition > NULL)
		return true;

	std::string messageWithoutPrefix = message.substr(possiblePrefixPosition + commandPrefix.size(), message.size() - commandPrefix.size());
	std::size_t possibleEndCommandPosition = messageWithoutPrefix.find(" ");

	if (possibleEndCommandPosition == std::string::npos)
		return !_commandHandler->TryExecute(session, messageWithoutPrefix); // Could be command without params.

	std::string commandName = messageWithoutPrefix.substr(possibleEndCommandPosition, possibleEndCommandPosition);

	return !_commandHandler->TryExecute(session, commandName);
}