#include "game_lobby_session.hpp"
#include "room_packet_handler.hpp"

GameLobbySession::GameLobbySession(Connection::Ptr conn) : Session(conn) 
{
	_connection->SetHandlers(
		std::bind(&GameLobbySession::HandlePacket, this, std::placeholders::_1),
		std::bind(&GameLobbySession::HandleClose, this));
};

GameLobbySession::~GameLobbySession()
{

}

void GameLobbySession::HandlePacket(ClientPacket& packet)
{
	handler->Execute(this, packet);
}

void GameLobbySession::HandleClose()
{
}
