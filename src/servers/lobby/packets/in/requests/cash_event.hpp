#ifndef CASH_EVENT_HPP
#define CASH_EVENT_HPP

#include "lobby_packet_event.hpp"
#include "lobby_session.hpp"
#include "shop_item.hpp"
#include "cash_response_event.hpp"
#include "lobby.hpp"
#include <vector>

class CashEvent : public LobbyPacketEvent {

public:
	void Read(LobbySession* session, ClientPacket& pack) override
	{
		uint32_t cash = session->Info()->Cash();
		//std::vector<ShopItem> items = session->GetLobby()->Shop()->List();
		session->Send(CashResponseEvent{ cash }.Compose(session));
		//session->Send(GoodsEvent{ items }.Compose(session));
	}
};

#endif