#ifndef DROP_CARD_EVENT_HPP
#define DROP_CARD_EVENT_HPP

#include <memory>
#include "lobby_packet_event.hpp"
#include "drop_card_response_event.hpp"
#include "inventory_manager.hpp"
#include "lobby_session.hpp"

class DropCardEvent : public LobbyPacketEvent {

public:
	DropCardEvent() : LobbyPacketEvent(sizeof(Packets::Lobby::DeleteCard)) {};
	void Read(LobbySession* session, ClientPacket& pack) override
	{
		auto packet = pack.Read<Packets::Lobby::DeleteCard>();

		uint32_t cardId = packet.cardId;
		if (session->Inventory()->RemoveItem(cardId))
			session->Send(DropCardResponseEvent{ cardId }.Compose(session));

	}
};

#endif