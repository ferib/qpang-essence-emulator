#ifndef EQUIP_ARMOR_EVENT_HPP
#define EQUIP_ARMOR_EVENT_HPP

#include "lobby_packet_event.hpp"
#include "lobby_session.hpp"
#include "equipment_manager.hpp"
#include "equip_armor_response_event.hpp"
#include "info_manager.hpp"
#include <cstdint>
#include <array>

class EquipArmorEvent : public LobbyPacketEvent {

public:
	EquipArmorEvent() : LobbyPacketEvent(sizeof(Packets::Lobby::EquipArmour)) {};
	void Read(LobbySession* session, ClientPacket& pack) override
	{
		auto packet = pack.Read<Packets::Lobby::EquipArmour>();

		uint16_t characterOffset = session->Equipment()->GetCharacterIndex(session->Info()->Character());

		session->Equipment()->SetEquipmentPart((EquipmentManager::Character)characterOffset, EquipmentManager::EquipmentSlot::HEAD, packet.head);
		session->Equipment()->SetEquipmentPart((EquipmentManager::Character)characterOffset, EquipmentManager::EquipmentSlot::FACE, packet.face);
		session->Equipment()->SetEquipmentPart((EquipmentManager::Character)characterOffset, EquipmentManager::EquipmentSlot::BODY, packet.body);
		session->Equipment()->SetEquipmentPart((EquipmentManager::Character)characterOffset, EquipmentManager::EquipmentSlot::HAND, packet.hands);
		session->Equipment()->SetEquipmentPart((EquipmentManager::Character)characterOffset, EquipmentManager::EquipmentSlot::BOTTOM, packet.pants);
		session->Equipment()->SetEquipmentPart((EquipmentManager::Character)characterOffset, EquipmentManager::EquipmentSlot::FOOT, packet.shoes);
		session->Equipment()->SetEquipmentPart((EquipmentManager::Character)characterOffset, EquipmentManager::EquipmentSlot::BACK, packet.back);
		session->Equipment()->SetEquipmentPart((EquipmentManager::Character)characterOffset, EquipmentManager::EquipmentSlot::SIDE, packet.side);

		std::array<uint64_t, 9> equipment = session->Equipment()->GetArmor((EquipmentManager::Character)characterOffset);

		session->Send(EquipArmorResponseEvent{ equipment, characterOffset }.Compose(session));
	}
};

#endif