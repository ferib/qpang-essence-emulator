#ifndef I_AM_SQUARE_EVENT_HPP
#define I_AM_SQUARE_EVENT_HPP

#include <cstdint>

#include "lobby_packet_event.hpp"
#include "lobby_session.hpp"

class IAmSquareEvent : public LobbyPacketEvent {

public:
	void Read(LobbySession* session, ClientPacket& pack) override
	{
		session->GetConnection()->SetEncryption(false);
		sLogger->Get()->info("Disable encryption for squareserver");
	}
};

#endif