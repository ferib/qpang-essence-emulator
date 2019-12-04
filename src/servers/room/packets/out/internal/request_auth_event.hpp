#ifndef REQUEST_AUTH_EVENT_HPP
#define REQUEST_AUTH_EVENT_HPP

#include "packet_event.hpp"
#include "connection.hpp"
#include "opcodes.hpp"
#include "packet_data.hpp"

class RequestAuthEvent : public PacketEvent
{
public:
	RequestAuthEvent(uint32_t playerId) { _playerId = playerId; };

	ServerPacket Compose(Connection::Ptr conn)
	{
		Packets::Lobby::RequestAuth rsp{};
		rsp.playerId = _playerId;
		return ServerPacket::Create<Opcode::ROOM_REQUEST_AUTH>(rsp);
	}
private:
	uint32_t _playerId;
};

#endif // !I_AM_ROOM_EVENT_HPP
