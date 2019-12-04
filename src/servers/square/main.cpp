//std
#include <cstdint>

#include "square_server.hpp"
#include "settings_manager.hpp"
#include "logger.hpp"

int32_t main()
{

	sLogger->Init("Squareserver");

	Database database{};
	{
		sSettings->Initialize();
		database.Close();
	}

	SquareServer squareServer{};
	squareServer.Initialize(
		Server::ALL_INTERFACES,
		8012,
		std::bind(&SquareServer::HandleAccept, &squareServer, std::placeholders::_1));
	squareServer.Accept();
	squareServer.Run();

	std::getchar();
}