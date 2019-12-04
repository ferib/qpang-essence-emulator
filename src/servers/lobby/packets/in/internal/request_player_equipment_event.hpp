#ifndef ROOM_REQUEST_PLAYER_EVENT_HPP
#define ROOM_REQUEST_PLAYER_EVENT_HPP

#include <memory>
#include "lobby_packet_event.hpp"
#include "lobby_session.hpp"
#include "packet_data.hpp"
#include "lobby.hpp"
#include "request_player_equipment_response_event.hpp"

class RequestPlayerEquipmentEvent : public LobbyPacketEvent {

public:
	void Read(LobbySession* session, ClientPacket& pack) override
	{
		auto data = pack.Read<Packets::Internal::RequestPlayerEquipment>();

		auto lobby = session->GetLobby();

		const auto playerIdentifier = data.playerId;

		auto target = lobby->FindSession(playerIdentifier);

		if (target != nullptr)
		{
			std::array<uint64_t, 9> armorIds = target->Equipment()->GetArmor(static_cast<EquipmentManager::Character>(target->Equipment()->GetCharacterIndex(target->Info()->Character())));
			std::array<uint64_t, 4> weaponIds = target->Equipment()->GetWeapons(static_cast<EquipmentManager::Character>(target->Equipment()->GetCharacterIndex(target->Info()->Character())));

			std::array<uint32_t, 9> armorItemIds;
			std::array<uint32_t, 4> weaponItemIds;

			for (size_t i = 0; i < armorIds.size(); i++)
			{
				armorItemIds[i] = target->Inventory()->GetItemByCardId(armorIds[i]).itemId;
			}

			for (size_t i = 0; i < weaponIds.size(); i++)
			{
				weaponItemIds[i] = target->Inventory()->GetItemByCardId(weaponIds[i]).itemId;
			}

			session->GetLobby()->GetRoom()->SendPacket(RequestPlayerEquipmentResponseEvent
			{
				target->Info()->Id(),
				target->Info()->Character(),
				armorItemIds,
				weaponItemIds,
				1
			}.Compose(nullptr));
		}

	}
};

#endif