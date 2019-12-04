#ifndef PLAYER_INFO_RESPONSE_EVENT_HPP
#define PLAYER_INFO_RESPONSE_EVENT_HPP

#include <memory>

#include "lobby_packet_event.hpp"
#include "packet_data.hpp"
#include <vector>
#include <cstdint>
#include <string>
#include "string_converter.hpp"
#include "equipment_manager.hpp"

class PlayerInfoResponseEvent : public LobbyPacketEvent {

public:
	PlayerInfoResponseEvent(uint32_t playerId, std::string nickname ,uint32_t level, uint32_t rank, uint32_t character, uint32_t experience, std::array<uint32_t, 13> equipment)
	{ 
		_playerId = playerId;
		_nickname = nickname;
		_level = level;
		_rank = rank;
		_character = character;
		_experience = experience;
		_equipment = equipment;
	};

	ServerPacket Compose(LobbySession* session) override 
	{
		Packets::Lobby::RequestPlayerInfoRsp rsp{};

		rsp.userId = _playerId;
		rsp.level = _level;
		rsp.rank = _rank;
		rsp.exp = _experience;
		wcsncpy(rsp.nickname, std::wstring(_nickname.begin(), _nickname.end()).data(), 16);

		rsp.character.characterId = _character;
		rsp.character.head = _equipment[EquipmentManager::HEAD];
		rsp.character.face = _equipment[EquipmentManager::FACE];
		rsp.character.body = _equipment[EquipmentManager::BODY];
		rsp.character.hands = _equipment[EquipmentManager::HAND];
		rsp.character.pants = _equipment[EquipmentManager::BOTTOM];
		rsp.character.boots = _equipment[EquipmentManager::FOOT];
		rsp.character.back = _equipment[EquipmentManager::BACK];
		rsp.character.side = _equipment[EquipmentManager::SIDE ];
		rsp.character.primaryWeapon.itemId = _equipment[EquipmentManager::PRIMARY];
		rsp.character.secondaryWeapon.itemId = _equipment[EquipmentManager::SECONDARY];
		rsp.character.meleeWeapon.itemId = _equipment[EquipmentManager::MELEE];
		rsp.character.throwWeapon.itemId = _equipment[EquipmentManager::THROW];

		return ServerPacket::Create<Opcode::LOBBY_PLAYERINFO_RSP>(rsp);
	};

private:
	uint32_t _playerId;
	std::string _nickname;
	uint32_t _level;
	uint32_t _rank;
	uint32_t _character;
	uint32_t _experience;
	std::array<uint32_t, 13> _equipment;
	
};

#endif