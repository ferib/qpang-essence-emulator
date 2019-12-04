#ifndef GOODS_EVENT_HPP
#define GOODS_EVENT_HPP

#include "lobby_packet_event.hpp"
#include "lobby_session.hpp"
#include "vector"
#include "shop_item.hpp"
#include "goods_response_event.hpp"

class GoodsEvent : public LobbyPacketEvent {

public:
	void Read(LobbySession* session, ClientPacket& pack) override
	{
		std::vector<ShopItem> items = session->GetLobby()->Shop()->List();
		session->Send(GoodsResponseEvent{items}.Compose(session));
	};
};

#endif