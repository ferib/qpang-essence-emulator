//std
#include <cstdint>
#include <iostream>

#include "auth_server.hpp"
#include "database.hpp"
#include "logger.hpp"
#include "settings_manager.hpp"

int32_t main()
{
	sLogger->Init("AuthServer");

	Database database{};
	{
		sSettings->Initialize();
		database.Close();
	}

	AuthServer server{};
	server.Initialize(
		Server::ALL_INTERFACES,
		8003,
		std::bind(&AuthServer::HandleAccept, &server, std::placeholders::_1));

	server.Accept();
	server.Run();
}