#ifndef I_AM_ROOM_EVENT_HPP
#define I_AM_ROOM_EVENT_HPP

#include <cstdint>

#include "lobby_packet_event.hpp"
#include "lobby_session.hpp"

#include "logger.hpp"

class IAmRoomEvent : public LobbyPacketEvent {

public:
	void Read(LobbySession* session, ClientPacket& pack) override
	{
		session->GetConnection()->SetEncryption(false);
		sLogger->Get()->info("Disabled encryption for roomserver");
	}
private:
};

#endif