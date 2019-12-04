#ifndef OPTION_CARDS_EVENT_HPP
#define OPTION_CARDS_EVENT_HPP

#include <memory>
#include "lobby_packet_event.hpp"
#include "option_cards_response_event.hpp"
#include <vector>
#include <cstdint>
#include "lobby_session.hpp"
#include "inventory_card.hpp"
#include "inventory_manager.hpp"

class GiftsEvent : public LobbyPacketEvent {

public:
	void Read(LobbySession* session, ClientPacket& pack) override
	{
		std::vector<InventoryCard> cards;
		session->Send(GiftsResponseEvent{cards}.Compose(session));
	}
};

#endif