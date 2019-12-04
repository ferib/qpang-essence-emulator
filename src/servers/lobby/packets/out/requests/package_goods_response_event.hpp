#ifndef PACKAGE_GOODS_RESPONSE_EVENT_HPP
#define PACKAGE_GOODS_RESPONSE_EVENT_HPP

#include "lobby_packet_event.hpp"
#include "packet_data.hpp"
#include <vector>

class PackageGoodsResponseEvent : public LobbyPacketEvent {

public:
	PackageGoodsResponseEvent() {  };

	ServerPacket Compose(LobbySession* session) override {
		Packets::Lobby::NormalGoodList rsp{};
		rsp.countInPacket = 0;
		rsp.totalCount = 0;
		rsp.unknown = 0;
		return ServerPacket::Create<Opcode::LOBBY_REQUEST_PACKAGE_GOODS_RSP>(rsp);
	};
private:
};

#endif