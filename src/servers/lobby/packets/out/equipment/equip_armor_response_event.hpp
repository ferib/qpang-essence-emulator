#ifndef EQUIP_ARMOR_RESPONSE_EVENT_HPP
#define EQUIP_ARMOR_RESPONSE_EVENT_HPP

#include "lobby_packet_event.hpp"
#include "packet_data.hpp"
#include <array>
#include <cstdint>
#include "equipment_manager.hpp"


class EquipArmorResponseEvent : public LobbyPacketEvent {

public:
	EquipArmorResponseEvent(std::array<uint64_t, 9> equipment, uint16_t characterOffset) { _equipment = equipment; _characterOffset = characterOffset; };

	ServerPacket Compose(LobbySession* session) override {
		Packets::Lobby::EquipArmourRsp rsp{};

		rsp.characterOffset = _characterOffset;
		rsp.head = _equipment[EquipmentManager::HEAD];
		rsp.face = _equipment[EquipmentManager::FACE];
		rsp.body = _equipment[EquipmentManager::BODY];
		rsp.hands = _equipment[EquipmentManager::HAND];
		rsp.pants = _equipment[EquipmentManager::BOTTOM];
		rsp.shoes = _equipment[EquipmentManager::FOOT];
		rsp.back = _equipment[EquipmentManager::BACK];
		rsp.side = _equipment[EquipmentManager::SIDE];

		return ServerPacket::Create<Opcode::LOBBY_EQUIP_ARMOUR_RSP>(rsp);
	};
private:
	std::array<uint64_t, 9> _equipment;
	uint16_t _characterOffset;
};

#endif