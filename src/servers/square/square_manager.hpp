#ifndef _SQUARE_MANAGER_HPP
#define _SQUARE_MANAGER_HPP

#include <cstdint>
#include <vector>
#include <memory>
#include "connection.hpp"
#include "square_session.hpp"
#include "square.hpp"
#include "settings_manager.hpp"

class SquareCommandHandler;
//TODO: Support for multiple channels.

class SquareManager
{
public:
	SquareManager();
	~SquareManager();

	std::shared_ptr<SquareSession> FindSession(uint32_t playerId);
	void AddSession(std::shared_ptr<SquareSession> session);
	bool HandleMessage(SquareSession* session, std::string message);

	std::vector<std::shared_ptr<Square>> List();
	std::shared_ptr<Square> GetSquare(uint32_t squareId);
	std::shared_ptr<Square> GetAvailableSquare();
	void Broadcast(ServerPacket packet);
	void SetLobbyServer(std::shared_ptr<Connection> lobbyServer);
	void RemoveSession(uint32_t playerId);
	std::shared_ptr<Connection> LobbyServer();
private:
	std::shared_ptr<Square> AddSquare();
	std::shared_ptr<Connection> _lobbyServer;
	std::vector<std::shared_ptr<SquareSession>> _sessions;
	std::vector<std::shared_ptr<Square>> _squares;
	
	SquareCommandHandler* _commandHandler;
	Logger* _logger;
};

#endif

