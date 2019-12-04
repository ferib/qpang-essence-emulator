#ifndef I_AM_LOBBY_HPP
#define I_AM_LOBBY_HPP

#include "game_lobby_session.hpp"
#include "room_packet_event.hpp"

class IAmLobbyEvent : public RoomPacketEvent
{
public:
	void Read(GameLobbySession* session, ClientPacket& pack) override
	{
		session->GetConnection()->SetEncryption(false);
		sLogger->Get()->info("Disabled encryption for lobbyserver");
	}
private:
};

#endif // !I_AM_LOBBY_HPP
