#ifndef OPEN_CARD_RESPONSE_EVENT_HPP
#define OPEN_CARD_RESPONSE_EVENT_HPP

#include "lobby_packet_event.hpp"
#include "packet_data.hpp"
#include <cstdint>
#include "inventory_card.hpp"
#include <string>
#include <time.h>
#include "string_converter.hpp"

class OpenCardResponseEvent : public LobbyPacketEvent {

public:
	OpenCardResponseEvent(InventoryCard card, uint32_t don) { _card = card; _don = don; };

	ServerPacket Compose(LobbySession* session) override {
		Packets::Lobby::OpenPlayerCardRsp rsp{};

		rsp.giftId = _card.id;
		rsp.don = _don;
		rsp.cardAmount = 1;
		rsp.card.cardId = _card.id;
		rsp.card.itemId = _card.itemId;
		rsp.card.opened = true;
		rsp.card.dateReceived = _card.timeCreated;
		rsp.card.type = _card.itemType;
		rsp.card.periodType = _card.periodType;
		rsp.card.period = _card.period;
		rsp.card.giftable = _card.giftable;
		rsp.card.boostLevel = _card.boostLevel;
		rsp.card.isBoosted = _card.boosted;
		rsp.card.hidden = false;
		rsp.card.unknown04 = 2; // ?
		rsp.card.unknown05 = 1; // ?

		return ServerPacket::Create<Opcode::LOBBY_OPEN_PLAYER_CARD_RSP>(rsp);
	};
private:
	InventoryCard _card;
	uint32_t _don;
};

#endif