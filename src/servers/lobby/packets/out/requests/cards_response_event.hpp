#ifndef CARDS_RESPONSE_EVENT_HPP
#define CARDS_RESPONSE_EVENT_HPP

#include "lobby_packet_event.hpp"
#include "packet_data.hpp"
#include <vector>
#include "inventory_card.hpp"

class CardsResponseEvent : public LobbyPacketEvent {

public:
	CardsResponseEvent(std::vector<InventoryCard> cards) { _cards = cards; };

	ServerPacket Compose(LobbySession* session) override {
		Packets::Lobby::InventoryCardsRsp rsp{};
		
		uint32_t size = _cards.size();
		rsp.unknown = _cards.size();
		rsp.totalCount = _cards.size();
		rsp.countInPacket = _cards.size();

		for (size_t i = 0; i < size; i++)
		{
			Packets::Lobby::InventoryCardsRsp::Card card;
			InventoryCard invCard = _cards.at(i);
			card.cardId = invCard.id;
			card.itemId = invCard.itemId;
			card.unknown01 = 0xA;
			card.unknown02 = 0xA;
			card.unknown03 = 0xA;
			card.unknown04 = 2;
			card.opened = invCard.opened;
			card.giftable = invCard.giftable;
			card.isBoosted = invCard.boosted;
			card.boostLevel = invCard.boostLevel;
			card.hidden = false; // ?
			card.unknown04 = false;
			card.unknown05 = true;
			card.unknown06 = true;
			//card.dateReceived = invCard.timeCreated;
			card.period = invCard.period;
			card.periodType = invCard.periodType;
			card.type = invCard.itemType;
			rsp.cards[i] = card;
		}
		return ServerPacket::Create<Opcode::LOBBY_INVENTORY_CARDS_RSP>(rsp);
	};
private:
	std::vector<InventoryCard> _cards;
};

#endif