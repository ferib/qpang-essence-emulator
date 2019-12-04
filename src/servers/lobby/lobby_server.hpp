#ifndef _LOBBY_SERVER_H
#define _LOBBY_SERVER_H

//std
#include <vector>
#include <array>

#include "lobby_session.hpp"
#include <net/server.hpp>

#include "connector.hpp"
#include "lobby.hpp"
#include "lobby_packet_handler.hpp"

class LobbyServer : public Server
{
	typedef Server Parent;

public:
	void HandleAccept(TcpSocket&& sock);
	void OnSquareServerConnected(Connector&);
	void OnAuthServerConnected(Connector&);
	void OnRoomServerConnected(Connector&);
	void Run();

	std::array<Connector*, 3> connectors = {
		new Connector("127.0.0.1", 8012, std::bind(&LobbyServer::OnSquareServerConnected, this, std::placeholders::_1)),
		new Connector("127.0.0.1", 8003, std::bind(&LobbyServer::OnAuthServerConnected, this, std::placeholders::_1)),
		new Connector("127.0.0.1", 8021, std::bind(&LobbyServer::OnRoomServerConnected, this, std::placeholders::_1)),
	};

private:
	std::vector<std::shared_ptr<LobbySession>> _sessions;
	LobbyPacketHandler* _packetHandler = new LobbyPacketHandler();
	Lobby::Ptr _lobby = std::make_shared<Lobby>();
};

#endif //_LOBBY_SERVER_H