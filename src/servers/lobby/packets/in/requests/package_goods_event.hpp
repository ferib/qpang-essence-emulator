#ifndef PACKAGE_GOODS_EVENT_HPP
#define PACKAGE_GOODS_EVENT_HPP

#include "lobby_packet_event.hpp"
#include "lobby_session.hpp"
#include "vector"
#include "inventory_card.hpp"
#include "inventory_manager.hpp"
#include "cards_response_event.hpp"
#include "package_goods_response_event.hpp"

class PackageGoodsEvent : public LobbyPacketEvent {

public:
	void Read(LobbySession* session, ClientPacket& pack) override
	{
		session->Send(PackageGoodsResponseEvent{}.Compose(session));
	};
};

#endif