#ifndef UPDATE_PLAYER_RESPONSE_EVENT_HPP
#define UPDATE_PLAYER_RESPONSE_EVENT_HPP

#include "square_packet_event.hpp"
#include "packet_data.hpp"
#include "square_session.hpp"
#include "square.hpp"
#include <cstdint>
#include <array>

class UpdatePlayerResponseEvent : public SquarePacketEvent {

public:
	UpdatePlayerResponseEvent(uint32_t playerId, uint16_t characterId, std::array<uint32_t, 9> equipment) { _playerId = playerId; _characterId = characterId; _equipment = equipment; };

	ServerPacket Compose(SquareSession* session) override
	{
		Packets::Square::ParkUpdatePlayer rsp{};
		rsp.targetId = _playerId;
		rsp.characterId = _characterId;
		rsp.equipment = _equipment;
		return ServerPacket::Create<Opcode::SQUARE_UPDATE_PLAYER>(rsp);
	};
private:
	uint32_t _playerId;
	uint16_t _characterId;
	std::array<uint32_t, 9> _equipment;
};

#endif