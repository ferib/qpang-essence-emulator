#ifndef GIFT_SHOP_CARD_EVENT_HPP
#define GIFT_SHOP_CARD_EVENT_HPP

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
#include "string_converter.hpp"
#include "offline_player.hpp"
#include "gift_shop_card_response_event.hpp"
#include "receive_gift_event.hpp"

class GiftShopCardEvent : public LobbyPacketEvent {

	enum Error {
		BUY_NOT_ENOUGH_MONEY = 303,
		BUY_ITEM_SOLD_OUT = 361,
		TARGET_NOT_EXIST = 365,
		BUY_FAIL_INVENTORY_FULL = 840,
	};

public:
	GiftShopCardEvent() : LobbyPacketEvent(sizeof(Packets::Lobby::GiftShopCard)){};
	void Read(LobbySession* session, ClientPacket& pack) override
	{
		auto packet = pack.Read<Packets::Lobby::GiftShopCard>();
		std::string targetNickname = StringConverter::WcharToString(packet.nickname, 16);

		if(targetNickname == session->Info()->Nickname())
			return session->SendError<Opcode::LOBBY_GIFT_ITEM_FAIL>(Error::TARGET_NOT_EXIST);

		if (!session->GetLobby()->ValidateNickname(targetNickname))
			return session->SendError<Opcode::LOBBY_GIFT_ITEM_FAIL>(Error::TARGET_NOT_EXIST);

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
				if (costsCash)
					cash = session->Info()->Cash(cash - itemToBuy.price);
				else
					don = session->Info()->Don(don - itemToBuy.price);


				auto target = session->GetLobby()->FindSession(targetNickname);
				if (target != nullptr)
				{
					// Send gift..
					InventoryCard invCard = target->Inventory()->AddItem(session->GetLobby()->Shop()->Buy(itemToBuy, target->Info()->Id()));

					if (invCard.id == NULL)
						return;
						
					session->Send(GiftShopCardResponseEvent{ costsCash, costsCash ? cash : don }.Compose(session));
					target->Send(ReceiveGiftEvent{ invCard, session->Info()->Nickname() }.Compose(target.get()));
				}
				else
				{
					OfflinePlayer offlinePlayer = session->GetLobby()->GetOfflinePlayer(targetNickname, OfflinePlayer::Type::MINIMAL);
					InventoryCard invCard = session->Inventory()->AddItem(session->GetLobby()->Shop()->Buy(itemToBuy, session->Info()->Id()));

					bool success = false;
					if (invCard.id == NULL)
						return;

					success = session->Inventory()->SendGift(offlinePlayer.playerId, invCard);
					if (success)
						session->Send(GiftShopCardResponseEvent{ costsCash, costsCash ? cash : don }.Compose(session));
					else
						return;
				}
			}
			else
				return session->SendError<Opcode::LOBBY_BUY_ITEM_FAIL>(Error::BUY_NOT_ENOUGH_MONEY);
		}
	}
};

#endif