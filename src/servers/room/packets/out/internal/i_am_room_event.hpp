#ifndef I_AM_ROOM_EVENT_HPP
#define I_AM_ROOM_EVENT_HPP

#include "packet_event.hpp"
#include "connection.hpp"
#include "opcodes.hpp"
#include "packet_data.hpp"

class IAmRoomEvent : public PacketEvent
{
public:
	ServerPacket Compose(Connection::Ptr conn)
	{
		Packets::Handshake::KeyExchange rsp{};
		return ServerPacket::Create<Opcode::I_AM_ROOM>(rsp);
	}
};

#endif // !I_AM_ROOM_EVENT_HPP
