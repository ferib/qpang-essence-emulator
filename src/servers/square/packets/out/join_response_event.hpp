#ifndef JOIN_RESPONSE_EVENT_HPP
#define JOIN_RESPONSE_EVENT_HPP

#include "square_packet_event.hpp"
#include "packet_data.hpp"
#include <memory>
#include "square.hpp"
#include "string_converter.hpp"

class JoinResponseEvent : public SquarePacketEvent {

public:
	JoinResponseEvent(Square::Ptr square) { _square = square; };

	ServerPacket Compose(SquareSession* session) override
	{
		Packets::Square::ParkJoinRsp rsp{};

		wcsncpy(rsp.name, StringConverter::StringToWString(_square->Name()).data(), 16);
		rsp.currPlayers = _square->List().size();
		rsp.maxPlayers = _square->MaxCapacity();
		rsp.parkId2 = _square->Id();
		rsp.parkId = _square->Id();
		rsp.state = _square->State();
		return ServerPacket::Create<Opcode::SQUARE_JOIN_PARK_RSP>(rsp);
	}
private:
	Square::Ptr _square;
};

#endif