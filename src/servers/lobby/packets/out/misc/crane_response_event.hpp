#ifndef CRANE_RESPONSE_EVENT_HPP
#define CRANE_RESPONSE_EVENT_HPP

#include <vector>
#include <cstdint>
#include "inventory_card.hpp"
#include "lobby_packet_event.hpp"
#include "player_info_response_event.hpp"
#include "lobby.hpp"
#include "lobby_session.hpp"

class CraneResponseEvent : public LobbyPacketEvent {

public:
	CraneResponseEvent(std::vector<InventoryCard> items, uint32_t coins, uint32_t don) { _items = items; _coins = coins; _don = don; };

	ServerPacket Compose(LobbySession* session) override
	{
		Packets::Lobby::UseCraneRsp rsp{};
		rsp.times = _items.size();
		rsp.newDon = _don;
		rsp.newCoins = _coins;

		for (size_t i = 0; i < rsp.times; i++)
		{
			Packets::Lobby::InventoryCardsRsp::Card card;
			InventoryCard invCard = _items.at(i);
			card.cardId = invCard.id;
			card.itemId = invCard.itemId;
			card.type = invCard.itemType;
			card.periodType = invCard.periodType;
			card.period = invCard.period;
			card.dateReceived = invCard.timeCreated;
			card.hidden = false;
			card.isBoosted = invCard.boosted;
			card.boostLevel = invCard.boostLevel;
			card.opened = true;
			card.unknown04 = 2;
			rsp.rewards[i].card = card;
			rsp.rewards[i].itemId = card.itemId;
		}
		return ServerPacket::Create<Opcode::LOBBY_USE_CRANE_RSP>(rsp);
	}
private:
	std::vector<InventoryCard> _items;
	uint32_t _don;
	uint32_t _coins;
};

#endif