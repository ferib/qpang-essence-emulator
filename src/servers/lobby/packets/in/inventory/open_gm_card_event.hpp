#ifndef OPEN_GM_CARD_EVENT_HPP
#define OPEN_GM_CARD_EVENT_HPP

#include <cstdint>
#include <memory>
#include <string>
#include "lobby_packet_event.hpp"
#include "inventory_manager.hpp"
#include "lobby_session.hpp"
#include "inventory_card.hpp"
#include "open_gm_card_response_event.hpp"

class OpenGMCardEvent : public LobbyPacketEvent {

public:
	OpenGMCardEvent() : LobbyPacketEvent{ sizeof(Packets::Lobby::OpenCard) } {};
	void Read(LobbySession* session, ClientPacket& pack) override
	{
		auto packet = pack.Read<Packets::Lobby::OpenCard>();
		InventoryCard inventoryCard = session->Inventory()->GetItemByCardId(packet.cardId);
		
		if (session->Inventory()->OpenGift(inventoryCard.id))
			session->Send(OpenGMCardResponseEvent{ inventoryCard }.Compose(session));
		
		// implement error.
	}
};

#endif