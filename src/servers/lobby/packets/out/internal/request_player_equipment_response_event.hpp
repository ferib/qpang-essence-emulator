#ifndef ROOM_REQUEST_PLAYER_EQUIPMENT_RESPONSE_EVENT_HPP
#define ROOM_REQUEST_PLAYER_EQUIPMENT_RESPONSE_EVENT_HPP

#include <array>
#include <string>
#include <cstdint>
#include "lobby_packet_event.hpp"
#include "string_converter.hpp"

class RequestPlayerEquipmentResponseEvent : public LobbyPacketEvent {

public:
	RequestPlayerEquipmentResponseEvent(uint32_t playerId, uint16_t characterId, std::array<uint32_t, 9> armor, std::array<uint32_t, 4> weapons, uint8_t cmd)
	{
		_playerId = playerId;
		_characterId = characterId;
		_armor = armor;
		_weapons = weapons;
		_cmd = cmd;
	};

	ServerPacket Compose(LobbySession* session) override
	{
		Packets::Internal::RequestPlayerEquipmentRsp rsp{};

		rsp.playerId = _playerId;
		rsp.character = _characterId;
		rsp.cmd = _cmd;
		rsp.armor = _armor;
		rsp.weapons = _weapons;

		return ServerPacket::Create<Opcode::ROOM_REQUEST_PLAYER_EQUIPMENT_RSP>(rsp);
	}
private:
	uint32_t _playerId;
	uint16_t _characterId;
	uint8_t _cmd;
	std::array<uint32_t, 9> _armor;
	std::array<uint32_t, 4> _weapons;
};

#endif