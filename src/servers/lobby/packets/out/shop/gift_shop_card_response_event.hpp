#ifndef GIFT_SHOP_CARD_RESPONSE_EVENT_HPP
#define GIFT_SHOP_CARD_RESPONSE_EVENT_HPP

#include "lobby_packet_event.hpp"
#include "packet_data.hpp"
#include "inventory_card.hpp"

class GiftShopCardResponseEvent : public LobbyPacketEvent {

public:
	GiftShopCardResponseEvent(bool isCash, int32_t newCurrencyAmount) { _isCash = isCash; _newCurrencyAmount = newCurrencyAmount; };

	ServerPacket Compose(LobbySession* session) override {
		Packets::Lobby::GiftShopCardRsp rsp{};
		rsp.currencyType = _isCash;
		rsp.moneyLeft = _newCurrencyAmount;
		return ServerPacket::Create<Opcode::LOBBY_SHOP_GIFT_RSP>(rsp);
	};
private:
	bool _isCash;
	int32_t _newCurrencyAmount;
};

#endif