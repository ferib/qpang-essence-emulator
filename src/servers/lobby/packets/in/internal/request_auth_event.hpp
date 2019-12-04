#ifndef REQUEST_AUTH_EVENT_HPP
#define REQUEST_AUTH_EVENT_HPP

#include <cstdint>
#include <vector>
#include <string>

#include "info_manager.hpp"
#include "equipment_manager.hpp"
#include "inventory_manager.hpp"

#include "lobby_packet_event.hpp"
#include "lobby_session.hpp"
#include "lobby.hpp"

#include "request_auth_response_event.hpp"

class RequestAuthEvent : public LobbyPacketEvent {

	enum CMD : uint32_t {
		SUCCESS = 1,
		FAIL = 2,
	};

public:
	void Read(LobbySession* session, ClientPacket& pack) override
	{
		auto packet = pack.Read<Packets::Lobby::RequestAuth>();

		auto target = session->GetLobby()->FindSession(packet.playerId);

		if (target != nullptr)
		{
			uint32_t playerId = target->Info()->Id();
			std::string nickname = target->Info()->Nickname();
			uint32_t experience = target->Info()->Experience();
			uint32_t prestige = target->Info()->Prestige();
			uint8_t rank = target->Info()->Rank();
			uint8_t level = target->Info()->Level();
			uint16_t characterId = target->Info()->Character();
			uint32_t don = target->Info()->Don();
			uint32_t cash = target->Info()->Cash();

			std::array<uint64_t, 13> cardIds = target->Equipment()->GetAllByCharacter((EquipmentManager::Character)target->Equipment()->GetCharacterIndex(target->Info()->Character()));
			std::array<uint32_t, 13> itemIds;

			for (size_t i = 0; i < itemIds.size(); i++)
			{
				itemIds[i] = target->Inventory()->GetItemByCardId(cardIds[i]).itemId;
			}

			return session->GetLobby()->GetRoom()->SendPacket(RequestAuthResponseEvent{
				CMD::SUCCESS,
				playerId,
				nickname,
				experience,
				prestige,
				rank,
				level,
				characterId,
				don,
				cash,
				cardIds,
				itemIds,
				}.Compose(nullptr));
		}

		session->GetLobby()->GetRoom()->SendPacket(RequestAuthResponseEvent{ CMD::FAIL, packet.playerId }.Compose(nullptr));
	}
};

#endif