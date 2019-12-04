#ifndef REMOVE_PLAYER_EVENT_HPP
#define REMOVE_PLAYER_EVENT_HPP

#include "square_packet_event.hpp"
#include "packet_data.hpp"
#include <cstdint>
#include "info_manager.hpp"
#include "square_session.hpp"
#include "string_converter.hpp"

class RemovePlayerEvent : public SquarePacketEvent {

public:
	RemovePlayerEvent(uint32_t playerId) { _playerId = playerId; };

	ServerPacket Compose(SquareSession* session) override
	{
		Packets::Square::ParkRemovePlayer rsp{};
		rsp.playerToRemove = _playerId;
		return ServerPacket::Create<Opcode::SQUARE_REMOVE_PLAYER>(rsp);
	}
private:
	uint32_t _playerId;
};

#endif