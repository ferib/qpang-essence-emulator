#ifndef I_AM_LOBBY_EVENT_HPP
#define I_AM_LOBBY_EVENT_HPP

#include <cstdint>
#include "square_packet_event.hpp"
#include "square_session.hpp"

class IAmLobbyEvent : public SquarePacketEvent {

public:
	void Read(SquareSession* session, ClientPacket& pack) override
	{
		session->GetConnection()->SetEncryption(false);
		sLogger->Get()->info("Disabled encryption for lobbyserver");
	}
private:
};

#endif