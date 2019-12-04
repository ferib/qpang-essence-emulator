#ifndef REQUEST_AUTH_RESPONSE_EVENT_HPP
#define REQUEST_AUTH_RESPONSE_EVENT_HPP

#include <cstdint>
#include <string>
#include <memory>
#include <vector>
#include "string_converter.hpp"
#include "lobby_packet_event.hpp"

class RequestAuthResponseEvent : public LobbyPacketEvent {

public:
	RequestAuthResponseEvent(uint32_t cmd, uint32_t playerId) { _cmd = cmd; _playerId = playerId; };
	RequestAuthResponseEvent(uint32_t cmd, uint32_t playerId, std::string nickname, uint32_t experience, uint32_t prestige, uint8_t rank, uint8_t level, uint16_t characterId, uint32_t don, uint32_t cash, std::array<uint64_t, 13> cardIds, std::array<uint32_t, 13> itemIds)
	{
		_cmd = cmd;
		_playerId = playerId;
		_nickname = nickname;
		_experience = experience;
		_prestige = prestige;
		_rank = rank;
		_level = level;
		_characterId = characterId;
		_cardIds = cardIds;
		_itemIds = itemIds;
		_cash = cash;
		_don = don;
	}


	ServerPacket Compose(LobbySession* session) override {
		Packets::Lobby::RequestAuthResponse rsp{};
		rsp.cmd = _cmd;
		rsp.playerId = _playerId;
		wcsncpy(rsp.nickname, std::wstring(_nickname.begin(), _nickname.end()).data(), 16);
		rsp.experience = _experience;
		rsp.prestige = _prestige;
		rsp.rank = _rank;
		rsp.level = _level;
		rsp.characterId = _characterId;
		rsp.cardIds = _cardIds;
		rsp.itemIds = _itemIds;
		rsp.cash = _cash;
		rsp.don = _don;
		return ServerPacket::Create<Opcode::ROOM_REQUEST_AUTH_RSP>(rsp);
	};
private:

	uint32_t _cmd;
	uint32_t _playerId;
	std::string _nickname;
	uint32_t _experience;
	uint32_t _prestige;
	uint8_t _rank;
	uint8_t _level;
	uint16_t _characterId;
	uint32_t _don;
	uint32_t _cash;

	std::array<uint64_t, 13> _cardIds;
	std::array<uint32_t, 13> _itemIds;
};

#endif