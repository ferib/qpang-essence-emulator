#ifndef I_AM_AUTH_EVENT_HPP
#define I_AM_AUTH_EVENT_HPP

#include <cstdint>

#include "packet_data.hpp"
#include "packet_event.hpp"

class IAmAuthEvent : public PacketEvent {

public:
	ServerPacket Compose(Connection::Ptr conn) override
	{
		Packets::Handshake::KeyExchange rsp{};
		return ServerPacket::Create<Opcode::I_AM_AUTH>(rsp);
	}
};

#endif