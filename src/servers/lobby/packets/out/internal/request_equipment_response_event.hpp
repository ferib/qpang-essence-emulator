#ifndef REQUEST_EQUIPMENT_RESPONSE_EVENT_HPP
#define REQUEST_EQUIPMENT_RESPONSE_EVENT_HPP

#include <array>
#include <string>
#include <cstdint>
#include "lobby_packet_event.hpp"
#include "string_converter.hpp"

class RequestEquipmentResponseEvent : public LobbyPacketEvent {

public:
	RequestEquipmentResponseEvent(std::array<uint32_t, 9> items, uint32_t playerId, uint8_t status, uint16_t level, uint8_t rank, uint16_t character, uint32_t prestige, std::string nickname)
	{
		_items = items;
		_playerId = playerId;
		_status = status;
		_level = level;
		_rank = rank;
		_character = character;
		_prestige = prestige;
		_nickname = nickname;
	};

	RequestEquipmentResponseEvent(bool status) { _status = status; };

	ServerPacket Compose(LobbySession* session) override
	{
		Packets::Internal::RequestEquipmentRsp rsp{};

		rsp.equipment = _items;
		rsp.playerId = _playerId;
		rsp.status = _status;
		rsp.level = _level;
		rsp.rank = _rank;
		rsp.character = _character;
		rsp.prestige = _prestige;
		wcsncpy(rsp.nickname, std::wstring(_nickname.begin(), _nickname.end()).data(), 16);

		return ServerPacket::Create<Opcode::REQUEST_EQUIPMENT_RSP>(rsp);
	}
private:
	std::array<uint32_t, 9> _items;
	std::string _nickname;
	uint32_t _playerId;
	uint8_t _status;
	uint16_t _level;
	uint8_t _rank;
	uint16_t _character;
	uint32_t _prestige;
};

#endif