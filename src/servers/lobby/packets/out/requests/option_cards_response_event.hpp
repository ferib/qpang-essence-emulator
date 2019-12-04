#ifndef OPTION_CARDS_RESPONSE_EVENT_HPP
#define OPTION_CARDS_RESPONSE_EVENT_HPP

#include "lobby_packet_event.hpp"
#include "packet_data.hpp"
#include <vector>
#include "inventory_card.hpp"
#include "string_converter.hpp"

class GiftsResponseEvent : public LobbyPacketEvent {

public:
	GiftsResponseEvent(std::vector<InventoryCard> cards) { _cards = cards; };


	ServerPacket Compose(LobbySession* session) override {
		Packets::Lobby::GiftsRsp rsp{};

		rsp.countInPacket = _cards.size();
		rsp.totalCount = _cards.size();
		rsp.unknown = _cards.size();

		for (size_t i = 0; i < _cards.size(); i++)
		{
			Packets::Lobby::GiftsRsp::GiftCard gift;
			InventoryCard card = _cards.at(i);

			gift.cardId = card.id;
			gift.dateReceived = card.timeCreated;
			gift.unk_02 = false; //??
			gift.unk_02 = card.id;

			rsp.cards[i] = gift;
		}

		return ServerPacket::Create<Opcode::LOBBY_GIFTS_RSP>(rsp);
	};
private:
	std::vector<InventoryCard> _cards;
};

#endif