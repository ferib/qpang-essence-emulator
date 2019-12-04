#ifndef REQUEST_AUTH_RESPONSE_EVENT_HPP
#define REQUEST_AUTH_RESPONSE_EVENT_HPP

#include "packet_data.hpp"
#include <memory>
#include "player.hpp"
#include "game.hpp"
#include "room_packet_event.hpp"
#include "room_info_manager.hpp"
#include "cg_auth.hpp"
#include "string_converter.hpp"

class RequestAuthResponseEvent : public RoomPacketEvent
{
public:
	void Read(GameLobbySession* session, ClientPacket& pack) override
	{
		auto packet = pack.Read<Packets::Lobby::RequestAuthResponse>();
		
		auto target = sGame->FindPlayer(packet.playerId);
		if (target != nullptr)
		{
			if (packet.cmd == 1)
			{
				//// ok
				target->SetName(StringConverter::WcharToString(packet.nickname, 16));
				target->SetCharacter(static_cast<Character>(packet.characterId));
				target->SetLevel(packet.level);
				target->SetRank(packet.rank);
				target->GetEquipment()->SetArmor(
					{
						packet.itemIds[0],
						packet.itemIds[1],
						packet.itemIds[2],
						packet.itemIds[3],
						packet.itemIds[4],
						packet.itemIds[5],
						packet.itemIds[6],
						packet.itemIds[7],
						packet.itemIds[8],
					});
				target->GetEquipment()->SetWeapons(
					{
						packet.itemIds[9],
						packet.itemIds[10],
						packet.itemIds[11],
						packet.itemIds[12],
					});
				target->SetPrestige(packet.prestige);
				target->SetExperience(packet.experience);
				target->Send(new CGAuth(packet.playerId, CGAuth::CMD::AUTHENTICATED));
			}
			else
			{
				// not ok
				target->Send(new CGAuth(packet.playerId, CGAuth::CMD::FAIL));
				//sGame->RemovePlayer(packet.playerId);
			}
		}
		else
			return;
	}
};

#endif // !I_AM_LOBBY_HPP
