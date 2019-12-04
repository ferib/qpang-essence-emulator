#ifndef I_AM_LOBBY_EVENT_HPP
#define I_AM_LOBBY_EVENT_HPP

#include <cstdint>

#include "packet_event.hpp"
#include "packet_data.hpp"
#include "auth_manager.hpp"
#include "logger.hpp"

class IamLobbyEvent : public PacketEvent {

public:
	void Read(Connection::Ptr conn, ClientPacket& pack) override
	{
		conn->SetEncryption(false);
		sLogger->Get()->debug("Disabled encryption for lobbyserver");
	}
private:
};

#endif