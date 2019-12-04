#ifndef EQUIP_WEAPON_EVENT_HPP
#define EQUIP_WEAPON_EVENT_HPP

#include "lobby_packet_event.hpp"
#include "lobby_session.hpp"
#include "equipment_manager.hpp"
#include "equip_weapon_response_event.hpp"
#include "info_manager.hpp"
#include <cstdint>
#include <array>
#include "update_stats_response_event.hpp"
#include "crane_response_event.hpp"
#include "update_level_event.hpp"

class EquipWeaponEvent : public LobbyPacketEvent {

public:
	EquipWeaponEvent() : LobbyPacketEvent(sizeof(Packets::Lobby::EquipWeapon)) {};

	void Read(LobbySession* session, ClientPacket& pack) override
	{
		auto packet = pack.Read<Packets::Lobby::EquipWeapon>();

		uint16_t characterOffset = session->Equipment()->GetCharacterIndex(session->Info()->Character());

		session->Equipment()->SetEquipmentPart((EquipmentManager::Character)characterOffset, EquipmentManager::EquipmentSlot::PRIMARY, packet.primary_card);
		session->Equipment()->SetEquipmentPart((EquipmentManager::Character)characterOffset, EquipmentManager::EquipmentSlot::SECONDARY, packet.secondary_card);
		session->Equipment()->SetEquipmentPart((EquipmentManager::Character)characterOffset, EquipmentManager::EquipmentSlot::MELEE, packet.melee_card);
		session->Equipment()->SetEquipmentPart((EquipmentManager::Character)characterOffset, EquipmentManager::EquipmentSlot::THROW, packet.throw_card);

		std::array<uint64_t, 4> equipment = session->Equipment()->GetWeapons((EquipmentManager::Character)characterOffset);

		session->Send(EquipWeaponResponseEvent{ equipment, characterOffset }.Compose(session));
	}
};

#endif