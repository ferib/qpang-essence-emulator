#ifndef EQUIP_WEAPON_RESPONSE_EVENT_HPP
#define EQUIP_WEAPON_RESPONSE_EVENT_HPP

#include "lobby_packet_event.hpp"
#include "packet_data.hpp"
#include <array>
#include <cstdint>


class EquipWeaponResponseEvent : public LobbyPacketEvent {

public:
	EquipWeaponResponseEvent(std::array<uint64_t, 4> equipment, uint16_t characterOffset) { _equipment = equipment; _characterOffset = characterOffset; };

	ServerPacket Compose(LobbySession* session) override {
		Packets::Lobby::EquipWeaponRsp rsp{};

		rsp.characterOffset = _characterOffset;
		rsp.primary_card = _equipment[0];
		rsp.secondary_card = _equipment[1];
		rsp.melee_card = _equipment[3];
		rsp.throw_card = _equipment[2];

		return ServerPacket::Create<Opcode::LOBBY_EQUIP_WEAPON_RSP>(rsp);
	};
private:
	std::array<uint64_t, 4> _equipment;
	uint16_t _characterOffset;
};

#endif