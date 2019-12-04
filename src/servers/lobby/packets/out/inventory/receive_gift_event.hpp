#ifndef RECEIVE_GIFT_EVENT_HPP
#define RECEIVE_GIFT_EVENT_HPP

#include "lobby_packet_event.hpp"
#include "packet_data.hpp"
#include <cstdint>
#include "inventory_card.hpp"
#include <string>
#include <time.h>
#include "string_converter.hpp"

class ReceiveGiftEvent : public LobbyPacketEvent {

public:
	ReceiveGiftEvent(InventoryCard card, std::string senderName) { _card = card; _senderName = senderName; };
	
	ServerPacket Compose(LobbySession* session) override {
		Packets::Lobby::ReceiveGift rsp{};
		rsp.cardId = _card.id;
		rsp.dateReceived = time(NULL);
		rsp.unknown = 1;
		wcsncpy(rsp.nickname, std::wstring(_senderName.begin(), _senderName.end()).data(), 16);
		return ServerPacket::Create<Opcode::LOBBY_RECEIVE_GIFT>(rsp);
	};
private:
	InventoryCard _card;
	std::string _senderName;
};

#endif