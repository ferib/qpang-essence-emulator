#ifndef OPEN_GM_CARD_RESPONSE_EVENT_HPP
#define OPEN_GM_CARD_RESPONSE_EVENT_HPP

#include "lobby_packet_event.hpp"
#include "packet_data.hpp"
#include <cstdint>
#include "inventory_card.hpp"
#include <string>
#include <time.h>
#include "string_converter.hpp"

class OpenGMCardResponseEvent : public LobbyPacketEvent {

public:
	OpenGMCardResponseEvent(InventoryCard card) { _card = card; };

	ServerPacket Compose(LobbySession* session) override {
		Packets::Lobby::OpenCardRsp rsp{};
		rsp.card.cardId = _card.id;
		rsp.card.itemId = _card.itemId;
		rsp.card.isBoosted = _card.boosted;
		rsp.card.boostLevel = _card.boostLevel;
		rsp.card.hidden = false; //...
		rsp.card.giftable = _card.giftable;
		rsp.card.type = _card.itemType;
		rsp.card.periodType = _card.periodType;
		rsp.card.period = _card.period;
		rsp.card.dateReceived = _card.timeCreated;
		rsp.card.opened = true;
		rsp.card.unknown04 = 2; // ?
		rsp.card.unknown05 = 1; // ?
		return ServerPacket::Create<Opcode::LOBBY_OPEN_GM_CARD_RSP>(rsp);
	};
private:
	InventoryCard _card;
};

#endif