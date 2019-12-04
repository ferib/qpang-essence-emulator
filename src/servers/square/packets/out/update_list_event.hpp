#ifndef UPDATE_LIST_EVENT_HPP
#define UPDATE_LIST_EVENT_HPP

#include "square_packet_event.hpp"
#include "packet_data.hpp"
#include <memory>
#include <cstdint>
#include "square.hpp"
#include "info_manager.hpp"
#include "square_session.hpp"
#include "string_converter.hpp"

class UpdateListEvent : public SquarePacketEvent {

public:
	enum CMD : uint8_t {
		UPDATE = 0,
		REMOVE = 1,
	};

	UpdateListEvent(Square::Ptr square, CMD command) { _square = square; _command = command; };

	ServerPacket Compose(SquareSession* session) override
	{
		Packets::Square::ParkUpdateParkList rsp{};
		rsp.parkId = _square->Id();
		rsp.cmd = _command;
		wcscpy(rsp.name, StringConverter::StringToWChar(_square->Name()));
		rsp.currPlayers = _square->Size();
		rsp.maxPlayers = _square->MaxCapacity();
		rsp.state = _square->State();
		return ServerPacket::Create<Opcode::SQUARE_UPDATE_LIST>(rsp);
	}
private:
	Square::Ptr _square;
	CMD _command;
};

#endif