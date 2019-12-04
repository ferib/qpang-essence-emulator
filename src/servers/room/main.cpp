//std
#include <cstdint>
#include <iostream>
#include <tnl/tnlLog.h>
#include "game.hpp"
#include "settings_manager.hpp"
#include "server.hpp"
#include "logger.hpp"

#define TNL_ENABLE_LOGGING

int32_t main()
{
	sLogger->Init("RoomServer");

	Database database{};
	{
		sSettings->Initialize();
		database.Close();
	}

	Server server{};
	server.Initialize(
		Server::ALL_INTERFACES,
		8021,
		std::bind(&Game::HandleConnectorConnection, sGame, std::placeholders::_1));
	server.Accept();

	boost::thread t2{ &Server::Run, &server };



	sGame->InitializeThreadPool(5);
	sGame->RunServer();
}