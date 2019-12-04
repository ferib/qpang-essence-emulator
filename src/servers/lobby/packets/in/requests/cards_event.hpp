#ifndef CARDS_EVENT_HPP
#define CARDS_EVENT_HPP

#include "lobby_packet_event.hpp"
#include "lobby_session.hpp"
#include "vector"
#include "inventory_card.hpp"
#include "inventory_manager.hpp"
#include "cards_response_event.hpp"

class CardsEvent : public LobbyPacketEvent {

public:
	void Read(LobbySession* session, ClientPacket& pack) override
	{
		std::vector<InventoryCard> cards = session->Inventory()->List();
		session->Send(CardsResponseEvent{ cards }.Compose(session));
	};
};

#endif