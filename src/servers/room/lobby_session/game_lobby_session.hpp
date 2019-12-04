#ifndef GAME_LOBBY_SESSION_HPP
#define GAME_LOBBY_SESSION_HPP

#include <net/session.hpp>

class RoomPacketHandler;

class GameLobbySession : public Session
{

public:
	using Ptr = std::shared_ptr<GameLobbySession>;
	GameLobbySession(Connection::Ptr connection);
	~GameLobbySession();
	void HandlePacket(ClientPacket& packet);
	void HandleClose();

	RoomPacketHandler* handler;
private:
};


#endif //GAME_LOBBY_SESSION_HPP