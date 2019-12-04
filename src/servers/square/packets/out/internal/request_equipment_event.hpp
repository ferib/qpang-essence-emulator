#ifndef REQUEST_EQUIPMENT_EVENT_HPP
#define REQUEST_EQUIPMENT_EVENT_HPP

#include <cstdint>
#include "square_packet_event.hpp"
#include "packet_data.hpp"

class RequestEquipmentEvent : public SquarePacketEvent {

public:
	RequestEquipmentEvent(uint32_t playerId) { _playerId = playerId; };

	ServerPacket Compose(SquareSession* session) override
	{
		Packets::Internal::RequestEquipment rsp{};
		rsp.playerId = _playerId;
		return ServerPacket::Create<Opcode::REQUEST_EQUIPMENT>(rsp);
	}
private:
	uint32_t _playerId;
};

#endif