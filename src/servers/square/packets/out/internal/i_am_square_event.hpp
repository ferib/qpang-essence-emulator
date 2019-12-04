#ifndef I_AM_SQUARE_EVENT_HPP
#define I_AM_SQUARE_EVENT_HPP

#include <cstdint>
#include "packet_event.hpp"
#include "packet_data.hpp"

class IAmSquareEvent : public PacketEvent {

public:
	ServerPacket Compose(Connection::Ptr session) override
	{
		Packets::Handshake::KeyExchange rsp{};
		return ServerPacket::Create<Opcode::I_AM_SQUARE>(rsp);
	}
};

#endif