#ifndef GIFT_CARD_EVENT_HPP
#define GIFT_CARD_EVENT_HPP

#include <cstdint>
#include <memory>
#include <string>
#include "lobby_packet_event.hpp"
#include "inventory_manager.hpp"
#include "lobby_session.hpp"
#include "string_converter.hpp"
#include "inventory_manager.hpp"
#include "gift_card_response_event.hpp"
#include "inventory_card.hpp"
#include "offline_player.hpp"
#include "receive_gift_event.hpp"
#include "shop_item.hpp"

class GiftCardEvent : public LobbyPacketEvent {

public:

	enum Error {
		TARGET_FULL_INV = 362,
		TARGET_NOT_EXIST = 365,
		CARD_UNGIFTABLE = 871,
		CARD_TARGET_LEVEL_LOW = CARD_UNGIFTABLE, // have to fix the right error code for this boy..
	};

	GiftCardEvent() : LobbyPacketEvent(sizeof(Packets::Lobby::GiftCard)) {};
	void Read(LobbySession* session, ClientPacket& pack) override
	{
		auto packet = pack.Read<Packets::Lobby::GiftCard>();

		std::string targetNickname = StringConverter::WcharToString(packet.nickname, 16);
		uint64_t cardId = packet.cardId;

		if (targetNickname == session->Info()->Nickname())
			return session->SendError<Opcode::LOBBY_GIFT_ITEM_FAIL>(Error::TARGET_NOT_EXIST);

		InventoryCard cardToGift = session->Inventory()->GetItemByCardId(cardId);

		if (!cardToGift.giftable)
			return session->SendError<Opcode::LOBBY_GIFT_ITEM_FAIL>(Error::CARD_UNGIFTABLE);

		if (!session->GetLobby()->ValidateNickname(targetNickname))
			return session->SendError<Opcode::LOBBY_GIFT_ITEM_FAIL>(Error::TARGET_NOT_EXIST);

		if (cardToGift.id == cardId)
		{
			auto target = session->GetLobby()->FindSession(targetNickname);
			if (target != nullptr)
			{
				//Target is online!

				if (target->Inventory()->List().size() >= 200)
					return session->SendError<Opcode::LOBBY_GIFT_ITEM_FAIL>(Error::TARGET_FULL_INV);

				if (target->Info()->Level() < session->GetLobby()->Shop()->GetItemByItemId(cardToGift.itemId).minLevel)
					return session->SendError<Opcode::LOBBY_SHOP_GIFT_FAIL>(Error::CARD_TARGET_LEVEL_LOW);

				bool gifted = session->Inventory()->SendGift(target->Info()->Id(), cardToGift);
				if (gifted)
				{
					// The item is now removed from our inventory, and updated to the target.
					cardToGift.ownerId = target->Info()->Id();
					if (target->Inventory()->ReceiveGift(cardToGift))
					{
						session->Send(GiftCardResponseEvent{ cardId }.Compose(session));
						target->Send(ReceiveGiftEvent{ cardToGift, session->Info()->Nickname() }.Compose(target.get()));
					}
					else
						return session->SendError<Opcode::LOBBY_GIFT_ITEM_FAIL>(Error::TARGET_FULL_INV);
				}
				else
					return session->SendError<Opcode::LOBBY_GIFT_ITEM_FAIL>(Error::CARD_UNGIFTABLE);
			}
			else
			{
				OfflinePlayer offPlayer = session->GetLobby()->GetOfflinePlayer(targetNickname, OfflinePlayer::Type::MINIMAL);
				ShopItem shopItem = session->GetLobby()->Shop()->GetItemByItemId(cardToGift.itemId);
				if(offPlayer.level < shopItem.minLevel)
					return session->SendError<Opcode::LOBBY_GIFT_ITEM_FAIL>(Error::CARD_TARGET_LEVEL_LOW);

				bool gifted = session->Inventory()->SendGift(offPlayer.playerId, cardToGift);

				if (gifted)
					session->Send(GiftCardResponseEvent{ cardId }.Compose(session));
				else
					return session->SendError<Opcode::LOBBY_GIFT_ITEM_FAIL>(Error::CARD_UNGIFTABLE);
			}
		}
	}
};

#endif