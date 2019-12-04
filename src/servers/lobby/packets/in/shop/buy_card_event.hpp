#ifndef BUY_CARD_EVENT_HPP
#define BUY_CARD_EVENT_HPP

#include <cstdint>
#include <memory>
#include "lobby_packet_event.hpp"
#include "buy_card_response_event.hpp"
#include "shop_manager.hpp"
#include "shop_item.hpp"
#include "inventory_card.hpp"
#include "lobby_session.hpp"
#include "info_manager.hpp"
#include "lobby.hpp"

class BuyCardEvent : public LobbyPacketEvent {

	enum Error {
		BUY_NOT_ENOUGH_MONEY = 303,
		BUY_ITEM_SOLD_OUT = 361,
		BUY_FAIL_INVENTORY_FULL = 840,
	};

public:
	BuyCardEvent() : LobbyPacketEvent(sizeof(Packets::Lobby::BuyItem)) {};
	void Read(LobbySession* session, ClientPacket& pack) override
	{
		auto packet = pack.Read<Packets::Lobby::BuyItem>();

		uint32_t sequenceId = packet.goodId;
		ShopItem itemToBuy = session->GetLobby()->Shop()->GetItemBySequenceId(sequenceId);

		if (itemToBuy.soldCount >= itemToBuy.stock)
			return session->SendError<Opcode::LOBBY_BUY_ITEM_FAIL>(Error::BUY_ITEM_SOLD_OUT);

		if (itemToBuy.sequenceId == sequenceId)
		{
			bool costsCash = itemToBuy.payType;
			int32_t don = session->Info()->Don();
			int32_t cash = session->Info()->Cash();

			int32_t left = costsCash ? cash - itemToBuy.price : don - itemToBuy.price;
	
			if (left >= 0)
			{
				InventoryCard inventoryCard = session->GetLobby()->Shop()->Buy(itemToBuy, session->Info()->Id());
				inventoryCard = session->Inventory()->AddItem(inventoryCard);

				if (inventoryCard.id == NULL)
					return session->SendError<Opcode::LOBBY_BUY_ITEM_FAIL>(Error::BUY_FAIL_INVENTORY_FULL);

				if (costsCash)
					session->Info()->Cash(cash - itemToBuy.price);
				else
					session->Info()->Don(don - itemToBuy.price);


				session->Send(BuyCardResponseEvent{ inventoryCard, costsCash, costsCash ? session->Info()->Cash() : session->Info()->Don() }.Compose(session));
			}
			else
				return session->SendError<Opcode::LOBBY_BUY_ITEM_FAIL>(Error::BUY_NOT_ENOUGH_MONEY);

		}
	}
};

#endif