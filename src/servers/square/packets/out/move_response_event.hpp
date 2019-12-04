#ifndef MOVE_RESPONE_EVENT_HPP
#define MOVE_RESPONE_EVENT_HPP

#include "square_packet_event.hpp"
#include "packet_data.hpp"
#include "square_session.hpp"
#include "square.hpp"
#include <array>

class MoveResponseEvent : public SquarePacketEvent {

public:
	MoveResponseEvent(uint32_t playerId, std::array<float, 3> position, uint8_t moveType, uint8_t moveDirection)
	{
		_playerId = playerId;
		_position = position;
		_moveType = moveType;
		_moveDirection = moveDirection;
	}

	ServerPacket Compose(SquareSession* session) override
	{
		Packets::Square::ParkMovePlayer rsp{};
		rsp.moveDirection = _moveDirection;
		rsp.moveType = _moveType;
		rsp.position = _position;
		rsp.targetId = _playerId;

		return ServerPacket::Create<Opcode::SQUARE_MOVE_PLAYER>(rsp);
	};
private:
	uint32_t _playerId;
	std::array<float, 3> _position;
	uint8_t _moveType;
	uint8_t _moveDirection;
};

#endif