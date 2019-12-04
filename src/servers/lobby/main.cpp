//std
#include <cstdint>

#include "lobby_server.hpp"
#include "database.hpp"
#include "logger.hpp"
#include "settings_manager.hpp"
#include <boost/thread.hpp>

int32_t main()
{

	sLogger->Init("LobbyServer");

	Database database{};
	{
		sSettings->Initialize();
		database.Close();
	}

	LobbyServer lobbyServer{};
	lobbyServer.Initialize(
		Server::ALL_INTERFACES,
		8005,
		std::bind(&LobbyServer::HandleAccept, &lobbyServer, std::placeholders::_1));
	lobbyServer.Accept();
	lobbyServer.Run();
}