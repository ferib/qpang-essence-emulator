#ifndef GOODS_RESPONSE_EVENT_HPP
#define GOODS_RESPONSE_EVENT_HPP

#include <cstdint>
#include "lobby_packet_event.hpp"
#include "packet_data.hpp"
#include <vector>
#include "shop_item.hpp"

class GoodsResponseEvent : public LobbyPacketEvent {

public:
	GoodsResponseEvent(std::vector<ShopItem> items) { _items = items; };

	ServerPacket Compose(LobbySession* session) override {
		Packets::Lobby::NormalGoodList rsp{};
		rsp.unknown = _items.size();
		rsp.totalCount = _items.size();
		rsp.countInPacket = _items.size();

		for (size_t i = 0; i < _items.size(); i++)
		{
			Packets::Lobby::NormalGoodList::NormalGood good = rsp.goods[i];
			ShopItem item = _items.at(i);
			good.goodId = item.sequenceId;
			good.unk_01 = item.itemId;
			good.payType = item.payType;
			good.price = item.price;
			good.stock = item.stock;
			good.category = item.state;
			rsp.goods[i] = good;
		}

		return ServerPacket::Create<Opcode::LOBBY_NORMAL_GOODS>(rsp);
	};
private:
	std::vector<ShopItem> _items;
};

#endif