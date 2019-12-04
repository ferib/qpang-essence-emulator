#ifndef UPDATE_LEVEL_EVENT_HPP
#define UPDATE_LEVEL_EVENT_HPP

#include <array>
#include <string>
#include <cstdint>
#include "lobby_packet_event.hpp"
#include "string_converter.hpp"

class UpdateLevelEvent : public LobbyPacketEvent {

public:
	UpdateLevelEvent(uint32_t playerId, uint16_t level)
	{
		_playerId = playerId;
		_level = level;
	};

	ServerPacket Compose(LobbySession* session) override
	{
		Packets::Internal::UpdatePlayerLevel rsp{};
		rsp.playerId = _playerId;
		rsp.level = _level;

		return ServerPacket::Create<Opcode::UPDATE_PLAYER_LEVEL>(rsp);
	}
private:
	uint32_t _playerId;
	uint16_t _level;
};

#endif