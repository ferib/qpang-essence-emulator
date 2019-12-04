#ifndef BUY_CARD_RESPONSE_EVENT_HPP
#define BUY_CARD_RESPONSE_EVENT_HPP

#include "lobby_packet_event.hpp"
#include "packet_data.hpp"
#include "inventory_card.hpp"

class BuyCardResponseEvent : public LobbyPacketEvent {

public:
	BuyCardResponseEvent(InventoryCard card, bool isCash, uint32_t newCurrencyAmount) { _card = card; _isCash = isCash; _newCurrencyAmount = newCurrencyAmount; };

	ServerPacket Compose(LobbySession* session) override {
		Packets::Lobby::BuyItemRsp rsp{};

		rsp.newAmount = _newCurrencyAmount;
		rsp.cardCount = 1;
		rsp.currencyType = _isCash;

		rsp.card.cardId = _card.id;
		rsp.card.itemId = _card.itemId;
		rsp.card.type = _card.itemType;
		rsp.card.period = _card.period;
		rsp.card.periodType = _card.periodType;
		rsp.card.hidden = false;
		rsp.card.giftable = true;
		rsp.card.boostLevel = _card.boostLevel;
		rsp.card.isBoosted = false;
		rsp.card.opened = true;
		rsp.card.dateReceived = _card.timeCreated;
		rsp.card.unknown04 = 2; // ?
		rsp.card.unknown05 = 1; // ?

		return ServerPacket::Create<Opcode::LOBBY_BUY_ITEM_RSP>(rsp);
	};
private:
	InventoryCard _card;
	bool _isCash;
	uint32_t _newCurrencyAmount;
};

#endif