#ifndef REQUEST_EQUIPMENT_EVENT_HPP
#define REQUEST_EQUIPMENT_EVENT_HPP

#include "lobby_packet_event.hpp"
#include "lobby_session.hpp"
#include "packet_data.hpp"
#include "request_equipment_response_event.hpp"
#include <array>
#include <string>
#include "lobby.hpp"
#include "equipment_manager.hpp"

class RequestEqupmentEvent : public LobbyPacketEvent {

public:
	void Read(LobbySession* session, ClientPacket& pack) override
	{
		auto packet = pack.Read<Packets::Internal::RequestEquipment>();
		auto lobby = session->GetLobby();
		auto square = lobby->GetSquare();

		auto targetPlayer = lobby->FindSession(packet.playerId);
		std::array<uint32_t, 9> equipmentItems;
		if (targetPlayer != nullptr)
		{
			//TODO: Cleanup seperate square equipment.
			uint8_t characterIndex = targetPlayer->Equipment()->GetCharacterIndex(targetPlayer->Info()->Character());
			std::array<uint64_t, 9> equipment = targetPlayer->Equipment()->GetArmor((EquipmentManager::Character)characterIndex);
			for (size_t i = 0; i < equipment.size() - 1; i++)
			{
				if (targetPlayer->Inventory()->HasItems())
					equipmentItems[i + 1] = targetPlayer->Inventory()->GetItemByCardId(equipment[i]).itemId;
				else
					equipmentItems[i + 1] = 0;
			}

			equipmentItems[0] = targetPlayer->Inventory()->GetItemByCardId(targetPlayer->Equipment()->GetEquipmentPart((EquipmentManager::Character)characterIndex, EquipmentManager::PRIMARY)).itemId;
			uint32_t playerId = targetPlayer->Info()->Id();
			uint16_t level = targetPlayer->Info()->Level();
			uint8_t rank = targetPlayer->Info()->Rank();
			uint16_t character = targetPlayer->Info()->Character();
			uint32_t prestige = targetPlayer->Info()->Prestige();
			std::string nickname = targetPlayer->Info()->Nickname();
			square->SendPacket(RequestEquipmentResponseEvent{ equipmentItems, playerId, true, level, rank, character, prestige, nickname }.Compose(session));
		}
		else
			square->SendPacket(RequestEquipmentResponseEvent{ false }.Compose(session));
	}
};

#endif