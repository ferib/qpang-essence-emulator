#ifndef REQUEST_PLAYER_EQUIPMENT_RESPONSE_EVENT_HPP
#define REQUEST_PLAYER_EQUIPMENT_RESPONSE_EVENT_HPP

#include "packet_data.hpp"
#include <memory>
#include "player.hpp"
#include "game.hpp"
#include "room_packet_event.hpp"

#include "gc_player_change.hpp"
#include "cg_player_change.hpp"

class RequestPlayerEquipmentResponseEvent : public RoomPacketEvent
{
public:
	void Read(GameLobbySession* session, ClientPacket& pack) override
	{
		auto packet = pack.Read<Packets::Internal::RequestPlayerEquipmentRsp>();

		auto target = sGame->FindPlayer(packet.playerId);
		if (target != nullptr)
		{
			if (packet.cmd == 1)
			{
				target->GetEquipment()->SetWeapons(packet.weapons);
				target->GetEquipment()->SetArmor(packet.armor);

				//Since we now loaded the equipment, the player is free to do whatever he wants =D
				target->SetState(PlayerState::IDLING);
			}
		}
	}
};

#endif // !I_AM_LOBBY_HPP
