#ifndef RELOAD_CRANE_EVENT_HPP
#define RELOAD_CRANE_EVENT_HPP

#include <cstdint>
#include "packet_event.hpp"
#include "packet_data.hpp"

class ReloadCraneEvent : public PacketEvent {

public:
	ServerPacket Compose(Connection::Ptr session) override
	{
		return ServerPacket::Create<Opcode::RELOAD_CRANE_COMMAND>(Packets::Handshake::KeyExchange{});
	}
};

#endif