#ifndef PLAYER_INFO_EVENT_HPP
#define PLAYER_INFO_EVENT_HPP

#include <memory>
#include "lobby_packet_event.hpp"
#include "player_info_response_event.hpp"
#include "lobby.hpp"
#include "lobby_session.hpp"
#include <vector>
#include <cstdint>
#include "offline_player.hpp"
#include "info_manager.hpp"
#include "equipment_manager.hpp"

class PlayerInfoEvent : public LobbyPacketEvent {

public:
	PlayerInfoEvent() : LobbyPacketEvent(sizeof(Packets::Lobby::RequestPlayerInfo)) {};
	void Read(LobbySession* session, ClientPacket& pack) override
	{
		auto packet = pack.Read<Packets::Lobby::RequestPlayerInfo>();

		auto target = session->GetLobby()->FindSession(packet.targetId);
		if (target != nullptr)
		{
			std::array<uint32_t, 13> equipmentItems;
			std::array<uint64_t, 13> equipmentCards = target->Equipment()->GetAllByCharacter((EquipmentManager::Character)target->Equipment()->GetCharacterIndex(target->Info()->Character()));

			for (size_t i = 0; i < EquipmentManager::EQUIPMENT_COUNT; i++)
			{
				equipmentItems[i] = target->Inventory()->GetItemByCardId(equipmentCards[i]).itemId;
			}

			session->Send(PlayerInfoResponseEvent
				{
					target->Info()->Id(),
					target->Info()->Nickname(),
					target->Info()->Level(),
					target->Info()->Rank(),
					target->Info()->Character(),
					target->Info()->Experience(),
					equipmentItems
				}.Compose(session));
		}
		else
		{
			OfflinePlayer offlinePlayer = session->GetLobby()->GetOfflinePlayer(packet.targetId, OfflinePlayer::Type::MEDIUM);
			if (offlinePlayer.playerId != NULL)
			{
				session->Send(PlayerInfoResponseEvent{offlinePlayer.playerId, offlinePlayer.nickname, offlinePlayer.level, offlinePlayer.rank, offlinePlayer.character
					, offlinePlayer.experience, offlinePlayer.equipment}.Compose(session));
			}
		}
	}
};

#endif