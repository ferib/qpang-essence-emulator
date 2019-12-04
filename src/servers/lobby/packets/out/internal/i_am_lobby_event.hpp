#ifndef I_AM_LOBBY_EVENT_HPP
#define I_AM_LOBBY_EVENT_HPP

#include <cstdint>
#include "packet_event.hpp"

class IAmLobbyEvent : public PacketEvent {

public:
	ServerPacket Compose(Connection::Ptr session) override
	{
		Packets::Handshake::KeyExchange rsp{};
		return ServerPacket::Create<Opcode::I_AM_LOBBY>(rsp);
	}
};

#endif